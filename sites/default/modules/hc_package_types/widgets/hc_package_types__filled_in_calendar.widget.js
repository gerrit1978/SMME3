/**
 * @file
 *
 */

(function ($) {

  Drupal.behaviors.cal_restrict_selection = {
    attach : function(context) {
      if (!$('body', context)) {
        return;
      } 
      
      $('.filled_in_calendar input').attr('disabled', true);
  
      var productId = $('input[name=product_id]').val();
			var widgetType = $('input[name=widget_type]').val();

			if (productId && widgetType == 'filled_in_calendar') {

	      $.getJSON(Drupal.settings.basePath + 'hc_package_types/filled_in_calendar/get_dates/' + productId, {}, function(data, textStatus, jqXHR) {
	          _event_days = data;
	          $('.filled_in_calendar input').attr('disabled', false);
	      });
	      
	      $('.filled_in_calendar input').datepicker({     
	        dateFormat: 'mm.dd.yy',
	        firstDay: 1, // first day is Monday
	
	      
	        beforeShowDay: function(date) { 
	          var day = (date.getMonth()+1) + '.' + date.getDate() + '.' + date.getFullYear();
	          if (_event_days[day])  {
	            return [true];
	          } else {
	            return [false];
	          }
	        }
	      });
	    }
    }
  };

})(jQuery);