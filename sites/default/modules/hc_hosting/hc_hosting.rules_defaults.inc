<?php
function hc_hosting_default_rules_configuration() {
  $configs = array();

  $rule = '{ "hc_smme_hosting" : {
    "LABEL" : "SMME Hosting",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "hc_hosting", "commerce_cart" ],
    "ON" : [ "commerce_cart_product_add" ],
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
      { "commerce_cart_product_add_by_sku" : {
          "USING" : {
            "user" : [ "site:current-cart-order:owner" ],
            "sku" : "HOSTING-US",
            "quantity" : "1",
            "combine" : 0
          },
          "PROVIDE" : { "product_add_line_item" : { "product_add_line_item" : "Added product line item" } }
        }
      }
    ]
  }
}';

  $configs['hc_smme_hosting'] = rules_import($rule);
  
  
  $rule = '{ "hc_smme_hosting_fixed_in_cart" : {
    "LABEL" : "SMME Hosting Fixed in Cart",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "commerce_cart" ],
    "ON" : [ "commerce_cart_product_remove" ],
    "IF" : [
      { "data_is" : { "data" : [ "commerce-product:sku" ], "value" : "HOSTING-US" } }
    ],
    "DO" : [
      { "commerce_cart_product_add_by_sku" : {
          "USING" : {
            "user" : [ "site:current-cart-order:owner" ],
            "sku" : "HOSTING-US",
            "quantity" : "1",
            "combine" : 0
          },
          "PROVIDE" : { "product_add_line_item" : { "product_add_line_item" : "Added product line item" } }
        }
      },
      { "drupal_message" : {
          "message" : "This line item cannot be removed from your cart.",
          "type" : "warning"
        }
      }
    ]
  }
}';
  
  
  $configs['hc_smme_hosting_fixed_in_cart'] = rules_import($rule);
  
  return $configs;
}

