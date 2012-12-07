<?php
function hc_hosting_default_rules_configuration() {
  $configs = array();

  $rule = '{ "rules_smme_hosting" : {
    "LABEL" : "SMME Hosting",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [
      "rules",
      "hc_hosting",
      "commerce_line_item",
      "commerce_product_reference"
    ],
    "ON" : [ "commerce_product_calculate_sell_price" ],
    "IF" : [
      { "entity_has_field" : {
          "entity" : [ "commerce-line-item" ],
          "field" : "field_course_line_item_hosting"
        }
      },
      { "data_is" : {
          "data" : [ "commerce-line-item:field-course-line-item-hosting" ],
          "value" : "smme"
        }
      },
      { "hc_hosting_fee" : { "commerce_line_item" : [ "commerce_line_item" ] } }
    ],
    "DO" : [
      { "commerce_line_item_unit_price_add" : {
          "commerce_line_item" : [ "commerce_line_item" ],
          "amount" : "99500",
          "component_name" : "base_price",
          "round_mode" : "1"
        }
      }
    ]
  }
}';

  $configs['hc_smme_hosting'] = rules_import($rule);
  return $configs;
}

