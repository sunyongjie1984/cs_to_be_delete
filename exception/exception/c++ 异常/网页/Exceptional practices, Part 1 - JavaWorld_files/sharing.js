//sharethis config
stLight.options({
	publisher:'b9cb359b-d324-4bc2-92eb-0060e771b347',
	onhover:false
});


//apply jQuery scrollfollow plugin
var doneOnce = false;

$( document ).ready( function () { //Don't fire if scroll fires before document.ready(), for example if the user scrolled to the bottom of a tall interstitial ad, clicked a link and then hit the back button
	window.onscroll = function () { //Same event that triggers scrollfollow
		if (doneOnce != true) {
			doneOnce = true; //Global. No need to run this on every scroll. Must set this value before the following statements or break Safari.
			if ($( '#body-content-area' ).height() > 0) {	 //If greater than zero, the interstitial isn't present or is finished loading so we can proceed
				//alert('body: '+$( '#body-content-area' ).height() +'sidecar: '+$( '#jw-sidecar' ).height());
				if ($( '#body-content-area' ).height() <= $( '#jw-sidecar' ).height()) {			
					//do nothing if container is shorter than (or same height as) sidecar
					//alert('short content');
				}
				else {
					$( '#jw-sidecar' ).scrollFollow( {
						container: 'body-content-area'
					});
					//alert('set scrollfollow');
				}
			}
		}
	}

});
