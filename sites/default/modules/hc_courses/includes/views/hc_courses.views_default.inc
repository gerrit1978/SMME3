<?php

/**
 * Views for the default product UI.
 */

/**
 * Implements hook_views_default_views().
 */
function hc_courses_views_default_views() {
  $views = array();

  /**
   * Training Domains View = Taxonomy terms 
   ***/
  $view = new view();
  $view->name = 'training_domains';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'SMME Training Domains';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Our Service Domains';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'training_domains' => 'training_domains',
  );
  
  /* Display: Footer Menu */
  $handler = $view->new_display('block', 'Footer Menu', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $translatables['training_domains'] = array(
    t('Master'),
    t('Our Service Domains'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Footer Menu'),
  );

  $views[$view->name] = $view;


  /**
   * Training Courses View = Content
   ***/
  $view = new view();
  $view->name = 'courses';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'SMME Courses';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Field: Valid for region (field_course_region) */
  $handler->display->display_options['arguments']['field_course_region_value']['id'] = 'field_course_region_value';
  $handler->display->display_options['arguments']['field_course_region_value']['table'] = 'field_data_field_course_region';
  $handler->display->display_options['arguments']['field_course_region_value']['field'] = 'field_course_region_value';
  $handler->display->display_options['arguments']['field_course_region_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_course_region_value']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['field_course_region_value']['default_argument_options']['code'] = '$user_location = $_SESSION[\'user_location\'];
    $continent_code = $user_location[\'continent_code\'];
    return $continent_code;';
  $handler->display->display_options['arguments']['field_course_region_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_course_region_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_course_region_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_course_region_value']['limit'] = '0';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'individual_package' => 'individual_package',
    'team_package' => 'team_package',
  );
  
  /* Display: Individual Course Packages */
  $handler = $view->new_display('block', 'Individual Course Packages', 'block_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Field: Valid for region (field_course_region) */
  $handler->display->display_options['arguments']['field_course_region_value']['id'] = 'field_course_region_value';
  $handler->display->display_options['arguments']['field_course_region_value']['table'] = 'field_data_field_course_region';
  $handler->display->display_options['arguments']['field_course_region_value']['field'] = 'field_course_region_value';
  $handler->display->display_options['arguments']['field_course_region_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_course_region_value']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['field_course_region_value']['default_argument_options']['code'] = '$user_location = $_SESSION[\'user_location\'];
    $continent_code = $user_location[\'continent_code\'];
    return $continent_code;';
  $handler->display->display_options['arguments']['field_course_region_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_course_region_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_course_region_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_course_region_value']['limit'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'individual_package' => 'individual_package',
  );
  
  /* Display: Team Course Packages */
  $handler = $view->new_display('block', 'Team Course Packages', 'block_3');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Field: Valid for region (field_course_region) */
  $handler->display->display_options['arguments']['field_course_region_value']['id'] = 'field_course_region_value';
  $handler->display->display_options['arguments']['field_course_region_value']['table'] = 'field_data_field_course_region';
  $handler->display->display_options['arguments']['field_course_region_value']['field'] = 'field_course_region_value';
  $handler->display->display_options['arguments']['field_course_region_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_course_region_value']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['field_course_region_value']['default_argument_options']['code'] = '$user_location = $_SESSION[\'user_location\'];
    $continent_code = $user_location[\'continent_code\'];
    return $continent_code;';
  $handler->display->display_options['arguments']['field_course_region_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_course_region_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_course_region_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_course_region_value']['limit'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'team_package' => 'team_package',
  );
  
  /* Display: Courses (region filter) */
  $handler = $view->new_display('page', 'Courses (region filter)', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Courses';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['view_mode'] = 'product_display_with_products';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'individual_package' => 'individual_package',
  );
  $handler->display->display_options['path'] = 'courses';
  
  /* Display: Courses (no region filter) */
  $handler = $view->new_display('page', 'Courses (no region filter)', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Courses';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['view_mode'] = 'product_display_with_products';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'individual_package' => 'individual_package',
  );
  $handler->display->display_options['path'] = 'all-courses';
  $translatables['courses'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('All'),
    t('Individual Course Packages'),
    t('Team Course Packages'),
    t('Courses (region filter)'),
    t('Courses'),
    t('Courses (no region filter)'),
  );






  $views[$view->name] = $view;

  return $views;
}
