/*jslint evil:true */
/**
 * Dynamic thread loader
 *
 * 
 * 
 * 
 * 
 * 
*/

// 
var DISQUS;
if (!DISQUS || typeof DISQUS == 'function') {
    throw "DISQUS object is not initialized";
}
// 

// json_data and default_json django template variables will close
// and re-open javascript comment tags

(function () {
    var jsonData, cookieMessages, session, key;

    /* */ jsonData = {"reactions": [], "reactions_limit": 10, "ordered_highlighted": [], "posts": {}, "ordered_posts": [], "realtime_enabled": true, "ready": true, "mediaembed": [], "has_more_reactions": false, "realtime_paused": false, "integration": {"receiver_url": "", "hide_user_votes": true, "reply_position": false, "disqus_logo": false}, "highlighted": {}, "reactions_start": 0, "media_url": "http://mediacdn.disqus.com/1321322654", "users": {}, "user_unapproved": {}, "messagesx": {"count": 0, "unread": []}, "thread": {"voters_count": 0, "offset_posts": 0, "slug": "exceptional_practices_part_1", "paginate": true, "num_pages": 0, "days_alive": 0, "moderate_none": false, "voters": {}, "total_posts": 0, "realtime_paused": true, "queued": false, "pagination_type": "append", "user_vote": null, "likes": 0, "num_posts": 0, "closed": false, "per_page": 20, "id": 416346682, "killed": false, "moderate_all": false}, "forum": {"use_media": false, "avatar_size": 32, "apiKey": "ubucnou7tk0UxUwcDELfiLLM9gCXmu7Aa8flyOi4YZmjsPU0YTNjXyAK5yBARn8O", "features": {"achievements": true, "training": true, "logs": true, "realtime": true, "support_implementation": true, "partner_key": true, "multiauthor_moderation": true, "support_vip": true, "reports": true, "vip_servers": true, "analytics": true, "sso": true, "multisite_admin": true, "uptime": true, "dtpl_editor": true}, "use_old_templates": false, "comment_max_words": 200, "mobile_theme_disabled": false, "linkbacks_enabled": false, "is_early_adopter": false, "allow_anon_votes": true, "revert_new_login_flow": false, "stylesUrl": "http://mediacdn.disqus.com/uploads/styles/75/8805/idg-javaworld.css", "login_buttons_enabled": false, "streaming_realtime": false, "show_avatar": true, "reactions_enabled": true, "reply_position": false, "id": 758805, "name": "JavaWorld", "language": "en", "mentions_enabled": true, "url": "idg-javaworld", "allow_anon_post": false, "disqus_auth_disabled": false, "thread_votes_disabled": false, "default_avatar_url": "http://mediacdn.disqus.com/1321322654/images/noavatar32.png", "ranks_enabled": false, "template": {"mobile": {"url": "http://mediacdn.disqus.com/1321322654/build/themes/newmobile.js", "css": "http://mediacdn.disqus.com/1321322654/build/themes/newmobile.css"}, "url": "http://mediacdn.disqus.com/1321322654/uploads/themes/t_a733fa9b25f33689e2adbe72199f0e62.js?62", "api": "1.1", "name": "Custom 5 (idg-computerworld)", "css": "http://mediacdn.disqus.com/1321322654/uploads/themes/t_a733fa9b25f33689e2adbe72199f0e62.css?62"}, "hasCustomStyles": false, "max_depth": 5, "lastUpdate": 1319588370, "moderate_all": false}, "settings": {"realtimeHost": "qq.disqus.com", "uploads_url": "http://media.disqus.com/uploads", "ssl_media_url": "https://securecdn.disqus.com/1321322654", "realtime_url": "http://rt.disqus.com/forums/realtime-cached.js", "facebook_app_id": "52254943976", "minify_js": true, "recaptcha_public_key": "6LdKMrwSAAAAAPPLVhQE9LPRW4LUSZb810_iaa8u", "read_only": false, "facebook_api_key": "4aaa6c7038653ad2e4dbeba175a679ba", "realtimePort": "80", "debug": false, "disqus_url": "http://disqus.com", "media_url": "http://mediacdn.disqus.com/1321322654"}, "ranks": {}, "request": {"sort": 2, "is_authenticated": false, "user_type": "anon", "subscribe_on_post": 0, "missing_perm": "login", "user_id": null, "remote_domain_name": "", "remote_domain": "", "is_verified": false, "profile_url": "", "username": "", "is_global_moderator": false, "sharing": {}, "timestamp": "2011-11-16_21:57:59", "is_moderator": false, "ordered_unapproved_posts": [], "unapproved_posts": {}, "forum": "idg-javaworld", "is_initial_load": true, "display_username": "", "points": null, "has_email": false, "moderator_can_edit": false, "is_remote": false, "userkey": "", "page": 1}, "context": {"use_twitter_signin": false, "use_fb_connect": false, "show_reply": true, "active_switches": ["bespin", "community_icon", "embedapi", "google_auth", "mentions", "new_facebook_auth", "new_thread_create", "realtime_cached", "show_captcha_on_links", "ssl", "static_reply_frame", "static_styles", "statsd_created", "upload_media", "use_rs_paginator_60m"], "sigma_chance": 10, "use_google_signin": false, "switches": {"olark_admin_addons": true, "listactivity_replies": true, "es_index_threads": true, "use_master_for_api": true, "google_auth": true, "html_email": true, "statsd.timings": true, "community_icon": true, "show_captcha_on_links": true, "send_to_akismet": true, "olark_admin_packages": true, "static_styles": true, "stats": true, "realtime": true, "realtime_cached": true, "statsd_created": true, "bespin": true, "olark_support": true, "olark_addons": true, "new_facebook_auth": true, "limit_get_posts_days_30d": true, "use_impermium": true, "use_akismet": true, "new_thread_create": true, "edits_to_spam": true, "upload_media": false, "vip_read_slave": true, "embedapi": true, "train_akismet": true, "ssl": true, "send_to_impermium": true, "train_impermium": true, "listactivity_replies_30d": true, "moderate_ascending": true, "stop_censorship": true, "new_moderate": true, "use_rs_paginator_60m": true, "redis_threadcount": true, "mentions": true, "olark_install": true, "static_reply_frame": true}, "forum_facebook_key": "", "use_yahoo": false, "subscribed": false, "active_gargoyle_switches": ["edits_to_spam", "es_index_threads", "html_email", "limit_get_posts_days_30d", "listactivity_replies", "listactivity_replies_30d", "moderate_ascending", "new_moderate", "olark_addons", "olark_admin_addons", "olark_admin_packages", "olark_install", "olark_support", "realtime", "redis_threadcount", "send_to_akismet", "send_to_impermium", "show_captcha_on_links", "stats", "statsd.timings", "stop_censorship", "train_akismet", "train_impermium", "use_akismet", "use_impermium", "use_master_for_api", "vip_read_slave"], "realtime_speed": 15000, "use_openid": false}}; /* */
    /* */ cookieMessages = {"user_created": null, "post_has_profile": null, "post_twitter": null, "post_not_approved": null}; session = {"url": null, "name": null, "email": null}; /* */

    DISQUS.jsonData = jsonData;
    DISQUS.jsonData.cookie_messages = cookieMessages;
    DISQUS.jsonData.session = session;

    if (DISQUS.useSSL) {
        DISQUS.useSSL(DISQUS.jsonData.settings);
    }

    // The mappings below are for backwards compatibility--before we port all the code that
    // accesses jsonData.settings to DISQUS.settings

    var mappings = {
        debug:                'disqus.debug',
        minify_js:            'disqus.minified',
        read_only:            'disqus.readonly',
        recaptcha_public_key: 'disqus.recaptcha.key',
        facebook_app_id:      'disqus.facebook.appId',
        facebook_api_key:     'disqus.facebook.apiKey'
    };

    var urlMappings = {
        disqus_url:    'disqus.urls.main',
        media_url:     'disqus.urls.media',
        ssl_media_url: 'disqus.urls.sslMedia',
        realtime_url:  'disqus.urls.realtime',
        uploads_url:   'disqus.urls.uploads'
    };

    if (DISQUS.jsonData.context.switches.realtime_setting_change) {
        urlMappings.realtimeHost = 'realtime.host';
        urlMappings.realtimePort = 'realtime.port';
    }
    for (key in mappings) {
        if (mappings.hasOwnProperty(key)) {
            DISQUS.settings.set(mappings[key], DISQUS.jsonData.settings[key]);
        }
    }

    for (key in urlMappings) {
        if (urlMappings.hasOwnProperty(key)) {
            DISQUS.jsonData.settings[key] = DISQUS.settings.get(urlMappings[key]);
        }
    }
}());

DISQUS.jsonData.context.csrf_token = '21bc467119200cb06806902fa8e2f5b0';

DISQUS.jsonData.urls = {
    login: 'http://disqus.com/profile/login/',
    logout: 'http://disqus.com/logout/',
    upload_remove: 'http://idg-javaworld.disqus.com/thread/exceptional_practices_part_1/async_media_remove/',
    request_user_profile: 'http://disqus.com/AnonymousUser/',
    request_user_avatar: 'http://mediacdn.disqus.com/1321322654/images/noavatar92.png',
    verify_email: 'http://disqus.com/verify/',
    remote_settings: 'http://idg-javaworld.disqus.com/_auth/embed/remote_settings/',
    edit_profile_window: 'http://disqus.com/embed/profile/edit/',
    embed_thread: 'http://idg-javaworld.disqus.com/thread.js',
    embed_vote: 'http://idg-javaworld.disqus.com/vote.js',
    embed_thread_vote: 'http://idg-javaworld.disqus.com/thread_vote.js',
    embed_thread_share: 'http://idg-javaworld.disqus.com/thread_share.js',
    embed_queueurl: 'http://idg-javaworld.disqus.com/queueurl.js',
    embed_hidereaction: 'http://idg-javaworld.disqus.com/hidereaction.js',
    embed_more_reactions: 'http://idg-javaworld.disqus.com/more_reactions.js',
    embed_subscribe: 'http://idg-javaworld.disqus.com/subscribe.js',
    embed_highlight: 'http://idg-javaworld.disqus.com/highlight.js',
    embed_block: 'http://idg-javaworld.disqus.com/block.js',
    update_moderate_all: 'http://idg-javaworld.disqus.com/update_moderate_all.js',
    update_days_alive: 'http://idg-javaworld.disqus.com/update_days_alive.js',
    show_user_votes: 'http://idg-javaworld.disqus.com/show_user_votes.js',
    forum_view: 'http://idg-javaworld.disqus.com/exceptional_practices_part_1',
    cnn_saml_try: 'http://disqus.com/saml/cnn/try/',
    realtime: DISQUS.jsonData.settings.realtime_url,
    thread_view: 'http://idg-javaworld.disqus.com/thread/exceptional_practices_part_1/',
    twitter_connect: DISQUS.jsonData.settings.disqus_url + '/_ax/twitter/begin/',
    yahoo_connect: DISQUS.jsonData.settings.disqus_url + '/_ax/yahoo/begin/',
    openid_connect: DISQUS.jsonData.settings.disqus_url + '/_ax/openid/begin/',
    googleConnect: DISQUS.jsonData.settings.disqus_url + '/_ax/google/begin/',
    community: 'http://idg-javaworld.disqus.com/community.html',
    admin: 'http://idg-javaworld.disqus.com/admin/moderate/',
    moderate: 'http://idg-javaworld.disqus.com/admin/moderate/',
    moderate_threads: 'http://idg-javaworld.disqus.com/admin/moderate-threads/',
    settings: 'http://idg-javaworld.disqus.com/admin/settings/',
    unmerged_profiles: 'http://disqus.com/embed/profile/unmerged_profiles/',

    channels: {
        def:      'http://disqus.com/default.html', /* default channel */
        auth:     'https://disqus.com/embed/login.html',
        tweetbox: 'http://disqus.com/forums/integrations/twitter/tweetbox.html?f=idg-javaworld',
        edit:     'http://idg-javaworld.disqus.com/embed/editcomment.html'
    }
};


// 
//     
DISQUS.jsonData.urls.channels.reply = 'http://mediacdn.disqus.com/1321322654/build/system/reply.html';
DISQUS.jsonData.urls.channels.upload = 'http://mediacdn.disqus.com/1321322654/build/system/upload.html';
DISQUS.jsonData.urls.channels.sso = 'http://mediacdn.disqus.com/1321322654/build/system/sso.html';
DISQUS.jsonData.urls.channels.facebook = 'http://mediacdn.disqus.com/1321322654/build/system/facebook.html';
//     
// 