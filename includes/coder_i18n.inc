<?php
// $Id$

/**
 * @file
 * This include file implements coder functionality to check for Internationalization issues.
 */

/**
 * Implementation of hook_reviews().
 */
function coder_i18n_reviews() {
  $argex = '(((\$?)[a-zA-Z_]+((\([^)]*\))|\[[^\]]*\])?)|[0-9]+(\.[0-9]*)?|\'\'|"")';
  $rules = array(
    array(
      '#type' => 'regex',
      '#value' => '[\s\(]l\s*\(\s*["\']',
      '#filename-not' => '\.install$',
      '#warning_callback' => '_coder_i18n_l_without_t',
    ),
    array(
      '#type' => 'regex',
      '#value' => '[\s\(]l\s*\(\s*[\'"]',
      '#function' => '_install$',
      '#warning_callback' => '_coder_i18n_in_install_l_without_st',
    ),
    array(
      '#type' => 'regex',
      '#value' => '[\s\(]t\s*\(\s*[\'"]',
      '#function' => '_install$',
      '#warning_callback' => '_coder_i18n_in_install_t',
    ),
    array(
      '#type' => 'regex',
      '#value' => '[\s\(]alert\s*\(\s*[\'"]',
      '#filename' => '\.js$',
      '#warning' => 'Javascript strings should be passed through Drupal.t().',
    ),
    array(
      '#type' => 'regex',
      '#value' => '#title\s*=>\s*[\'"][\'"]',
      '#warning_callback' => '_coder_i18n_fapi_title_without_t',
    ),
    array(
      '#type' => 'regex',
      '#value' => 'form_error\s*\(\s*'. $argex .'\s*,\s*[\'"]',
      '#warning_callback' => '_coder_i18n_form_error_without_t',
    ),
    array(
      '#type' => 'regex',
      '#value' => '[\'"]title[\'"]\s*=>\s*[\'"][^<]',
      '#warning_callback' => '_coder_i18n_in_hook_links_without_t',
      '#source' => 'allphp',
      '#function' => '_link$',
    ),
    array(
      '#type' => 'regex',
      '#value' => 'drupal_set_title\s*\(\s*[\'"]',
      '#warning_callback' => '_coder_i18n_drupal_set_title_without_t',
    ),
    array(
      '#type' => 'regex',
      '#value' => 'drupal_set_message\s*\(\s*[\'"]',
      '#warning_callback' => '_coder_i18n_drupal_set_message_without_t',
    ),
    array(
      '#type' => 'regex',
      '#value' => 'watchdog\s*\(\s*'. $argex .'\s*,\s*s?t\(',
      '#warning_callback' => '_coder_i18n_watchdog_with_t',
    ),
  );
  $review = array(
    '#title' => t('Internationalization'),
    '#rules' => $rules,
    '#severity' => 'major',
  );
  return array('i18n' => $review);
}

/**
 * Define the warning callbacks.
 */

function _coder_i18n_l_without_t() {
  return array(
    '#warning' => t('The $text argument to !l() should be enclosed within !t() so that it is translatable.',
      array(
        '!l' => theme('drupalapi', 'l'),
        '!t' => theme('drupalapi', 't'),
      )
    ),
  );
}

function _coder_i18n_in_install_l_without_st() {
  return array(
    '#warning' => t('The $text argument to !l() should be enclosed within !st() so that it is translatable from within the install.',
      array(
        '!l' => theme('drupalapi', 'l'),
        '!st' => theme('drupalapi', 'st'),
      )
    ),
  );
}

function _coder_i18n_in_install_t() {
  return array(
    '#warning' => t('Use !get_t() or !st() instead of !t() in !hook_install(), !hook_uninstall() and !hook_update_N()',
      array(
        '!get_t' => theme('drupalapi', 'get_t'),
        '!st' => theme('drupalapi', 'st'),
        '!t' => theme('drupalapi', 't'),
        '!hook_install' => theme('drupalapi', 'hook_install'),
        '!hook_uninstall' => theme('drupalapi', 'hook_uninstall'),
        '!hook_update_N' => theme('drupalapi', 'hook_update_N'),
      )
    ),
  );
}

function _coder_i18n_fapi_title_without_t() {
  return array(
    '#warning' => t('The FAPI #title should be enclosed within !t() so that it is translatable.',
      array(
        '!l' => theme('drupalapi', 'l'),
        '!t' => theme('drupalapi', 't'),
      )
    ),
  );
}

function _coder_i18n_form_error_without_t() {
  return array(
    '#warning' => t('The $message argument to !form_error() should be enclosed within !t() so that it is translatable.',
      array(
        '!form_error' => theme('drupalapi', 'form_error'),
        '!t' => theme('drupalapi', 't'),
      )
    ),
  );
}

function _coder_i18n_in_hook_links_without_t() {
  return array(
    '#warning' => t("The 'title' option should be enclosed within !t() so that it is translatable.",
      array(
        '!t' => theme('drupalapi', 't'),
      )
    ),
  );
}

function _coder_i18n_drupal_set_message_without_t() {
  return array(
    '#warning' => t('The $message argument to !drupal_set_message() should be enclosed within !t() so that it is translatable.',
      array(
        '!drupal_set_message' => theme('drupalapi', 'drupal_set_message'),
        '!t' => theme('drupalapi', 't'),
      )
    ),
  );
}

function _coder_i18n_drupal_set_title_without_t() {
  return array(
    '#warning' => t('The $title argument to !drupal_set_title() should be enclosed within !t() so that it is translatable.',
      array(
        '!drupal_set_title' => theme('drupalapi', 'drupal_set_title'),
        '!t' => theme('drupalapi', 't'),
      )
    ),
  );
}

function _coder_i18n_watchdog_with_t() {
  return array(
    '#warning' => t('The $message argument to !watchdog() should NOT be enclosed within !t(), so that it can be properly translated later into the language of the administrator viewing the logs.',
      array(
        '!watchdog' => theme('drupalapi', 'watchdog'),
        '!t' => theme('drupalapi', 't'),
      )
    ),
  );
}
