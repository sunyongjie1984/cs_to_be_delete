var i18n = { 
	start_editing: 'Fehler entdeckt? Korrigieren Sie ihn in Ihrem Browser!', 
	ajax_form: '/ajax/edit.html', 
	ajax_post: '/ajax/edit.php', 
	success_first: 'Ihre Änderungen wurden auf dem Server als Verbesserungsvorschläge gespeichert. Nach einer Freigabe durch den Autor sind Ihre Verbesserungvorschläge permanent sichtbar.', 
	success_second: 'Vielen Dank für Ihre neuen Verbesserungsvorschläge - sie wurden ebenfalls gespeichert.' 
}; 

$(function() { 
	var lang = $('[lang]').attr('lang'); 
	if (lang == 'en') { 
		i18n = { 
			start_editing: 'Found an error? Fix it in your browser!', 
			ajax_form: '/ajax/edit.html', 
			ajax_post: '/ajax/edit.php', 
			success_first: 'Your feedback has been saved. After a review by the author your changes will be permanent and visible to everyone.', 
			success_second: 'Thank you for your additional feedback - it was also saved!' 
		}; 
	} 
}); 

// See http://benalman.com/projects/jquery-unwrap-plugin/ 
$.fn.unwrap = function () { 
	return this.each(function() { 
		$(this.childNodes).insertBefore(this); 
	}).remove(); 
}; 

/* 
// See http://refactormycode.com/codes/341-jquery-all-descendent-text-nodes-within-a-node 
$.fn.textNodes = function() { 
	var textNodes = []; 
	$.each(this[0].childNodes, function() { 
		if (this.nodeType == Node.TEXT_NODE) 
			textNodes.push(this); 
		else 
			$.each(this.childNodes, arguments.callee); 
	}); 
	return textNodes; 
}; 
*/ 

function Editor(sel) { 
	var editor = this; 
	this.selector = sel || 'div.chapter div.sect1 p:not(.solution)'; 

	$(this.selector).bind('keypress', function(e) { 
		if (e.keyCode == 13) { 
			e.preventDefault(); 
		} 
	}).each(function() { 
		$(this).data('original', $(this).clone()); 
		$(this).data('current', $(this).clone()); 
	}); 

	$(document.body).append($('<div class="ajax">').load(i18n.ajax_form, null, function(responseText, textStatus) { 
		if (textStatus == 'success') { 
			$('.menu').css('display', 'none').bind('dragstart', function(e) { 
				if (!$(e.target).is('.menu .title')) 
					return false; 
			}).bind('drag', function(e) { 
				$(this).css({ 
					top: e.offsetY - (document.body.scrollTop ? document.body.scrollTop : document.documentElement.scrollTop), 
					left: e.offsetX - (document.body.scrollLeft ? document.body.scrollLeft : document.documentElement.scrollLeft) 
				}); 
			}); 

			$('.menu .title a').click(function() { 
				$('.menu').hide(); 
				editableText(false); 
				selectableKeywords(false); 
			}); 

			$('.menu input:radio[name=edit]').click(function() { 
				if ($('.menu input:radio[name=edit]:checked').val() == '1') { 
					editableText(true); 
					selectableKeywords(false); 
				} else { 
					editableText(false); 
					selectableKeywords(true); 
				} 
			}); 

			$('#btnSave').click(function() { 
				save(); 
			}); 

			$('#btnReset').click(function() { 
				reset(); 
			}); 

			$('.notice').css('display', 'none'); 
		} 
	})); 

	this.show = function() { 
		$('.menu').show(); 
		if ($('.menu input:radio[name=edit]:checked').val() == '1') { 
			editableText(true); 
			selectableKeywords(false); 
		} else { 
			editableText(false); 
			selectableKeywords(true); 
		} 
	} 

	function hide() { 
		$('.menu').hide(); 
		editableText(false); 
		selectableKeywords(false); 
	} 

	function editableText(b) { 
		$(editor.selector).attr('contentEditable', b).toggleClass('editable', b); 
	} 

	$('.keyword.selected, .keyword.hover').live('click', function(e) { 
		$(this).toggleClass('hover').toggleClass('selected'); 
	}); 

	var r = document.body.createTextRange ? document.body.createTextRange() : null; 

	function selectableKeywords(b) { 
		if (b) { 
			$('.keyword').addClass('selected'); 
			$(editor.selector).css({ 
				cursor: 'pointer' 
			}); 

			if (document.body.createTextRange) { 
				$(editor.selector).bind('mousemove', function(e) { 
					if (document.selection.type != 'None') { 
						return; 
					} 

					var closest = $(e.target).closest('.keyword'); 
					if (closest.length) { 
						if (closest.is('.selected')) 
							$('.keyword.hover').unwrap(); 
						return; 
					} 

					try { 
						r.moveToPoint(e.clientX, e.clientY); 
						$('.keyword.hover').unwrap(); 
						r.expand('word'); 
						if (r.text.match(/[\wäöüß]/i)) { 
							while (!r.text.match(/[^\wäöüß\-+]/i)) { 
								r.moveEnd('character', 1); 
								var closest = $(r.parentElement()).closest(editor.selector); 
								if (closest == null || closest.get(0) != this) 
									break; 
							} 
							r.moveEnd('character', -1); 
							while (!r.text.match(/[^\wäöüß\-+]/i)) { 
								r.moveStart('character', -1); 
								var closest = $(r.parentElement()).closest(editor.selector); 
								if (closest == null || closest.get(0) != this) 
									break; 
							} 
							r.moveStart('character', 1); 
							if (r.text == r.htmlText) { 
								r.pasteHTML('<span class="keyword hover">' + r.text + '</span>'); 
							} else { 
								if ($(r.htmlText).is('.keyword.selected')) { 
									$(r.htmlText).toggleClass('hover').toggleClass('selected'); 
								} else 
									r.pasteHTML('<span class="keyword hover">' + r.htmlText + '</span>'); 
							} 
						} 
					} catch(ex) { 
					} 
				}).bind('mouseleave', function(e) { 
					$('.keyword.hover').unwrap(); 
				}); 
			} else { 
				$('.keyword').live('mouseover', function(e) { 
					if ($(this).hasClass('selected')) 
						return; 
					$(this).addClass('hover'); 
				}).live('mouseout', function() { 
					$(this).removeClass('hover'); 
				}); 

				$(editor.selector).bind('mouseenter', function(e) { 
					var res = $(this).html().match(/([\wäöüß\-+]+)|([^\wäöüß\-+]+)/gi); 
					var html = ''; 
					var tagIndent = 0; 
					var entityIndent = 0; 
					$.each(res, function(i, val) { 
						tagIndent += val.split('<').length - 1; 
						if (tagIndent > 0) 
							tagIndent -= val.split('>').length - 1; 
						entityIndent += val.split('&').length - 1; 
						if (entityIndent > 0) 
							entityIndent -= val.split(';').length - 1; 
						if (!tagIndent && !entityIndent && val.match(/[\wäöüß]/i)) 
							html += '<span class="keyword">' + val + '</span>'; 
						else 
							html += val; 
					}); 
					$(this).html(html).find('.keyword:has(:only-child.keyword)').children().unwrap(); 
					/* 
					// UNFINISHED ATTEMPT TO COMBINE WORDS WHICH SPAN ELEMENTS (eg. "<code>for</code>-loop") 
					$('.keyword:not(.selected)').unwrap(); 
					this.normalize(); 
					var textNodes = $(this).textNodes(); 
					$.each(textNodes, function(i, node) { 
						while (node != null && ( (word = /[\wäöüß\-+]+/i.exec(node.nodeValue)) != null)) { 
							var r = document.createRange(); 
							r.setStart(node, word.index); 
							r.setEnd(node, word.index + word[0].length); 
							var parent = $(document.createElement('span')).addClass('keyword').get(0); 
							r.surroundContents(parent); 
							parent.parentNode.normalize(); 
							node = parent.nextSibling; 
						} 
					}); 
					*/ 
				}).bind('mouseleave', function(e) { 
					$('.keyword:not(.selected)').unwrap(); 
				}); 
			} 
		} else { 
			$(editor.selector).css({ 
				cursor: 'default' 
			}); 

			if (document.body.createTextRange) { 
				$(editor.selector).unbind('mousemove').unbind('mouseleave'); 
				$('.keyword').removeClass('selected'); 
			} else { 
				$(editor.selector).unbind('mouseenter').unbind('mouseleave'); 
				$('.keyword').die('mouseover').die('mouseout'); 
				$('.keyword').removeClass('selected'); 
			} 
		} 
	} 

	var savedOnce = false; 

	function save() { 
		var sent = false; 
		$(editor.selector).each(function() { 
			if ($(this).html() != $(this).data('original').html() && 
				$(this).html() != $(this).data('current').html()) { 
				$(this).data('current', $(this).clone()); 
				var data = { 
					'url': location.href, 
					'title': document.title, 
					'old': $(this).data('original').text(), 
					'new': $(this).text(), 
					'oldHtml': $(this).data('original').html(), 
					'newHtml': $(this).html() 
				}; 
				$.post(i18n.ajax_post, data); 
				sent = true; 
			} 
		}); 
		if (sent) { 
			if (!savedOnce) { 
				message(i18n.success_first); 
				savedOnce = true; 
			} else { 
				message(i18n.success_second); 
			} 
		} 
	} 

	function reset() { 
		$(editor.selector).each(function() { 
			$(this).html($(this).data('original').html()); 
		}); 
	} 

	function message(text) { 
		var note = $('.notice:first').clone(); 
		note.find('.message').text(text); 
		$('.notices').append(note.css('display', 'block')); 
		setTimeout(function() { 
			note.animate({ 
				opacity: 0, 
				height: 0 
			}, 'swing', function() { 
				$(this).css('display', 'none'); 
			}); 
		}, 8000); 
	} 
} 

$(function() { 
	if (location.hostname.search(/(^|\.)highscore\.de$/i) != -1) { 
		editor = new Editor(); 
		$('div.chapter p.license:first').each(function() { 
			var p = $('<p class="edit">'); 
			var a = $('<a href="javascript:;">' + i18n.start_editing + '</a>').click(function() { 
				editor.show(); 
			}); 
			p.append(a); 
			$(this).after(p); 
		}); 
	} 
}); 

$(function() { 
	$('div.tip').prev().each(function() { 
		var a = $('<a href="javascript:;">Tipp?</a>'); 
		$(this).append(a); 
		a.click(function() { 
			$(this).parent().next().toggle(); 
		}); 
	}); 
}); 
