<?php

/**
* Implementation of hook_rules_condition_info().
*/
function hc_coupon_rules_condition_info() {
  return array(
    'hc_coupon_coupon_region_is_valid' => array(
      'group' => 'HC Coupons',
      'label' => t('Region is valid'),
      'arguments' => array(
        'commerce_line_item' => array(
          'type' => 'commerce_line_item', 
          'label' => t('line item')
        ),
        'commerce_coupon' => array(
          'type' => 'commerce_coupon',
          'label' => t('coupon'),
        ),
      ),
      'module' => 'hc_coupon',
    ),
    'hc_coupon_fixed_coupon_region_is_valid' => array(
      'group' => 'HC Coupons',
      'label' => t('Region for fixed coupon is valid'),
      'arguments' => array(
        'commerce_coupon' => array(
          'type' => 'commerce_coupon',
          'label' => t('coupon'),
        ),
      ),
      'module' => 'hc_coupon',
    ),
    
  );
}




/**
 * Callback function for rules condition: PCT coupon
 */
function hc_coupon_coupon_region_is_valid($commerce_line_item, $commerce_coupon) {


  $fields_line_item = entity_metadata_wrapper('commerce_line_item', $commerce_line_item);
  $fields_coupon = entity_metadata_wrapper('commerce_coupon', $commerce_coupon);

  $coupon_region = $fields_coupon->field_course_region->value();  
	if (!is_array($coupon_region)) {
	  $coupon_region = array($coupon_region);
	}


  $line_item_display_path = $fields_line_item->commerce_display_path->value();
  $line_item_display_path_split = explode('/', $line_item_display_path);
  $nid_display = $line_item_display_path_split[1];
  
  $fields_node = entity_metadata_wrapper('node', $nid_display);
  
  $product_region = $fields_node->field_course_region->value();

	if (!is_array($product_region)) {
	  $product_region = array($product_region);
	}

  if (in_array($product_region[0], $coupon_region)) {
    return TRUE;
  } else {
    return FALSE;
  }

}


/**
 * Callback function for rules condition: FIXED coupon
 */
function hc_coupon_fixed_coupon_region_is_valid($commerce_coupon) {

  // coupon region
  $fields_coupon = entity_metadata_wrapper('commerce_coupon', $commerce_coupon);
  $coupon_region = $fields_coupon->field_course_region->value();

  // user region
  $user_location = $_SESSION['user_location'];
  $continent_code = $user_location['continent_code'];
  
  if ($continent_code == $coupon_region) {
    return TRUE;
  } else {
    return FALSE;
  }
}