<?php

//exit('Widget Fixed dates ingeladen');

/*
 * @file
 *
 * Nomenclature: MODULE_NAME__WIDGET_NAME__HOOK_NAME
 *
 * e.g. hc_package_types__fixed_dates__menu

/********************************************************
 * SUBHOOKS
 *******************************************************/

/**
 * Subhook for hook_menu
 *
 * This is called from the main module's hook_menu
 * and allows other modules to register additional URLs
 * necessary for business logic
 *
 * URLs should always have a name with following structure:
 * MODULE_NAME/WIDGET_NAME/ACTION_NAME/parameters
 */
function hc_package_types__fixed_dates__menu() {
  return array();
}

/**
 * Subhook for rendering the default form element for selecting dates
 */
function hc_package_types__fixed_dates__default_form_element($product_id) {
  $element = array();

  $element['#weight'] = '20';

  $element['#type'] = 'select';
  $element['#options'] = _hc_package_types__fixed_dates__options($product_id);
  
  return $element;
}


/**
 * Subhook validation function
 */
function hc_package_types__fixed_dates__validate(&$form, &$form_state) {
  $values = $form_state['values'];
  $chosen_date = $values['product_package_type'];
  
  $product_id = $values['product_id'];
  $fields = entity_metadata_wrapper('commerce_product', $product_id);

  $package_type = $fields->field_package_type->value();
  $package_dates = $fields->field_package_date->value();

  $product_type = $fields->type->value();
  
  if ($product_type != 'team_package') {
    return TRUE;
  }

  if (!(isset($package_dates[$chosen_date]['value']))) {
    form_set_error('product_package_type', t('Please make a choice.'));
    return FALSE;
  }

}


/**
 * Subhook submit function
 */
function hc_package_types__fixed_dates__submit(&$form, &$form_state) {
  $values = $form_state['values'];

  $product_id = $values['product_id'];
  $product_package_type = $values['product_package_type'];    
  
  $fields = entity_metadata_wrapper('commerce_product', $product_id);
  
  $product_type = $fields->type->value();

  $package_type = $fields->field_package_type->value();
  $package_dates = $fields->field_package_date->value();

	if ($product_type == 'team_package') {
	  $line_item_date = $package_dates[$product_package_type]['value'];
    // get line item
    $line_item = entity_metadata_wrapper('commerce_line_item', $form_state['line_item']);
  
  	$line_item->field_course_line_item_date->set($line_item_date);
  	$line_item->save();
  }

}



/********************************************************
 * INTERNAL HELPER FUNCTIONS
 *******************************************************/



/**
 * Helper function for rendering the options
 */
function _hc_package_types__fixed_dates__options($product_id) {
  $options = array();
  
  $fields = entity_metadata_wrapper('commerce_product', $product_id);
  $dates = $fields->field_package_date->value();
  
  if (is_array($dates)) {
    foreach ($dates as $date) {
      $time = strtotime($date['value']);
      $timezone = $date['timezone'];
      $formatted_date = format_date($time, 'custom', 'm.d.Y', $timezone);
      $options[] = $formatted_date;
    }
  }

  return $options;

}