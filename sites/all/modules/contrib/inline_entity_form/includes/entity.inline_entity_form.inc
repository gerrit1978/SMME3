<?php

/**
 * @file
 * Defines the base inline entity form controller.
 */

class EntityInlineEntityFormController {

  public $entityType;
  public $settings;

  public function __construct($entityType, array $settings) {
    $this->entityType = $entityType;
    $this->settings = $settings + $this->defaultSettings();
  }

  /**
   * Returns an array of css filepaths for the current entity type, keyed
   * by theme name.
   *
   * If provided, the "base" CSS file is included for all themes.
   * If a CSS file matching the current theme exists, it will also be included.
   *
   * @code
   * return array(
   *   'base' => drupal_get_path('module', 'test_module') . '/css/inline_entity_form.base.css',
   *   'seven' => drupal_get_path('module', 'test_module') . '/css/inline_entity_form.seven.css',
   * );
   * @endcode
   */
  public function css() {
    return array();
  }

  /**
   * Returns an array of entity type labels (singular, plural) fit to be
   * included in the UI text.
   */
  public function labels() {
    $labels = array(
      'singular' => t('entity'),
      'plural' => t('entities'),
    );

    $info = entity_get_info($this->entityType);
    // Commerce and its contribs declare permission labels that can be used
    // for more precise and user-friendly strings.
    if (!empty($info['permission labels'])) {
      $labels = $info['permission labels'];
    }

    return $labels;
  }

  /**
   * Returns an array of fields (which can be either Field API fields or
   * properties defined through hook_entity_property_info()) that should be
   * used to represent a selected entity in the IEF table.
   *
   * The IEF widget can have its own fields specified in the widget settings,
   * in which case the output of this function is ignored.
   *
   * @param $bundles
   *   An array of allowed $bundles for this widget.
   *
   * @return
   *   An array of field information, keyed by field name. Allowed keys:
   *   - type: 'field' or 'property',
   *   - label: Human readable name of the field, shown to the user.
   *   - weight: The position of the field relative to other fields.
   *   - visible: Whether the field should be displayed.
   *   Special keys for type 'field':
   *   - formatter: The formatter used to display the field, or "hidden".
   *   - settings: An array passed to the formatter. If empty, defaults are used.
   *   - delta: If provided, limits the field to just the specified delta.
   */
  public function defaultFields($bundles) {
    $info = entity_get_info($this->entityType);
    $metadata = entity_get_property_info($this->entityType);

    $fields = array();
    if (!empty($info['entity keys']['label'])) {
      $label_key = $info['entity keys']['label'];
      $fields[$label_key] = array(
        'type' => 'property',
        'label' => $metadata ? $metadata['properties'][$label_key]['label'] : t('Label'),
        'visible' => TRUE,
        'weight' => 1,
      );
    }
    else {
      $id_key = $info['entity keys']['id'];
      $fields[$id_key] = array(
        'type' => 'property',
        'label' => $metadata ? $metadata['properties'][$id_key]['label'] : t('ID'),
        'visible' => TRUE,
        'weight' => 1,
      );
    }
    if (count($bundles) > 1) {
      $bundle_key = $info['entity keys']['bundle'];
      $fields[$bundle_key] = array(
        'type' => 'property',
        'label' => $metadata ? $metadata['properties'][$bundle_key]['label'] : t('Type'),
        'visible' => TRUE,
        'weight' => 2,
      );
    }

    return $fields;
  }

  /**
   * Returns an array of default settings in the form of key => value.
   */
  public function defaultSettings() {
    $defaults = array();
    $defaults['allow_existing'] = FALSE;
    $defaults['match_operator'] = 'CONTAINS';
    $defaults['delete_references'] = FALSE;

    return $defaults;
  }

  /**
   * Returns the settings form for the current entity type.
   *
   * The settings form is embedded into the IEF widget settings form.
   * Settings are later injected into the controller through $this->settings.
   *
   * @param $field
   *   The definition of the reference field used by IEF.
   * @param $instance
   *   The definition of the reference field instance.
   */
  public function settingsForm($field, $instance) {
    $labels = $this->labels();

    $form = array();
    $form['allow_existing'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow users to add existing @label.', array('@label' => $labels['plural'])),
      '#default_value' => $this->settings['allow_existing'],
    );
    $form['match_operator'] = array(
      '#type' => 'select',
      '#title' => t('Autocomplete matching'),
      '#default_value' => $this->settings['match_operator'],
      '#options' => array(
        'STARTS_WITH' => t('Starts with'),
        'CONTAINS' => t('Contains'),
      ),
      '#description' => t('Select the method used to collect autocomplete suggestions. Note that <em>Contains</em> can cause performance issues on sites with thousands of nodes.'),
      '#states' => array(
        'visible' => array(
          ':input[name="instance[widget][settings][type_settings][allow_existing]"]' => array('checked' => TRUE),
        ),
      ),
    );
    $form['delete_references'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete referenced @label when the parent entity is deleted.', array('@label' => $labels['plural'])),
      '#default_value' => $this->settings['delete_references'],
    );

    return $form;
  }

  /**
   * Returns the entity form to be shown through the IEF widget.
   *
   * When adding data to $form_state it should be noted that there can be
   * several IEF widgets on one master form, each with several form rows,
   * leading to possible key collisions if the keys are not prefixed with
   * $entity_form['#parents'].
   *
   * @param $entity_form
   *   The entity form.
   * @param $form_state
   *   The form state of the parent form.
   */
  public function entityForm($entity_form, &$form_state) {
    $info = entity_get_info($this->entityType);
    $entity = $entity_form['#entity'];

    if (!empty($info['fieldable'])) {
      field_attach_form($this->entityType, $entity, $entity_form, $form_state, LANGUAGE_NONE);
    }

    return $entity_form;
  }

  /**
   * Validates the entity form.
   *
   * @param $entity_form
   *   The entity form.
   * @param $form_state
   *   The form state of the parent form.
   */
  public function entityFormValidate($entity_form, &$form_state) {
    $info = entity_get_info($this->entityType);
    $entity = $entity_form['#entity'];

    if (!empty($info['fieldable'])) {
      field_attach_form_validate($this->entityType, $entity, $entity_form, $form_state, LANGUAGE_NONE);
    }
  }

  /**
   * Handles the submission of an entity form.
   *
   * Prepares the entity stored in $entity_form['#entity'] for saving by copying
   * the values from the form to matching properties and, if the entity is
   * fieldable, invoking Field API submit.
   *
   * @param $entity_form
   *   The entity form.
   * @param $form_state
   *   The form state of the parent form.
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    $info = entity_get_info($this->entityType);
    list(, , $bundle) = entity_extract_ids($this->entityType, $entity_form['#entity']);
    $entity = $entity_form['#entity'];
    $entity_values = drupal_array_get_nested_value($form_state['values'], $entity_form['#parents']);

    // Copy top-level form values that are not for fields to entity properties,
    // without changing existing entity properties that are not being edited by
    // this form. Copying field values must be done using field_attach_submit().
    $values_excluding_fields = $info['fieldable'] ? array_diff_key($entity_values, field_info_instances($this->entityType, $bundle)) : $entity_values;
    foreach ($values_excluding_fields as $key => $value) {
      $entity->$key = $value;
    }

    if ($info['fieldable']) {
      field_attach_submit($this->entityType, $entity, $entity_form, $form_state);
      $this->cleanupFieldFormState($entity_form, $form_state);
    }
  }

  /**
   * Cleans up the form state for each field.
   *
   * After field_attach_submit() has run and the entity has been saved, the form
   * state still contains field data in $form_state['field']. Unless that
   * data is removed, the next form with the same #parents (reopened add form,
   * for example) will contain data (i.e. uploaded files) from the previous form.
   *
   * @param $entity_form
   *   The entity form.
   * @param $form_state
   *   The form state of the parent form.
   */
  protected function cleanupFieldFormState($entity_form, &$form_state) {
    list(, , $bundle) = entity_extract_ids($entity_form['#entity_type'], $entity_form['#entity']);
    $instances = field_info_instances($entity_form['#entity_type'], $bundle);
    foreach ($instances as $instance) {
      $field_name = $instance['field_name'];
      $parents = $entity_form[$field_name]['#parents'];
      array_pop($parents);
      $langcode = $entity_form[$field_name]['#language'];

      $field_state = field_form_get_state($parents, $field_name, $langcode, $form_state);
      unset($field_state['items']);
      $field_state['items_count'] = 0;
      field_form_set_state($parents, $field_name, $langcode, $form_state, $field_state);
    }
  }

  /**
   * Returns the delete form to be shown through the IEF widget.
   *
   * @param $delete_form
   *   The delete form.
   * @param $form_state
   *   The form state of the parent form.
   */
  public function deleteForm($delete_form, &$form_state) {
    $entity_label = entity_label($this->entityType, $delete_form['#entity']);
    $delete_form['message'] = array(
      '#markup' => '<div>' . t('Are you sure you want to delete %label?', array('%label' => $entity_label)) . '</div>',
    );

    return $delete_form;
  }

  /**
   * Permanently saves the given entity.
   *
   * @param $entity
   *   The entity to save.
   * @param array $context
   *   Available keys:
   *   - parent_entity_type: The type of the parent entity.
   *   - parent_entity: The parent entity.
   */
  public function save($entity, $context) {
    entity_save($this->entityType, $entity);
  }

  /**
   * Delete permanently saved entities.
   *
   * @param $ids
   *   An array of entity IDs.
   * @param array $context
   *   Available keys:
   *   - parent_entity_type: The type of the parent entity.
   *   - parent_entity: The parent entity.
   */
  public function delete($ids, $context) {
    entity_delete_multiple($this->entityType, $ids);
  }
}
