<?php

/**
 * @file
 * This file contains a class to include the Tuque php library.
 */

require_once 'tuque_wrapper.inc';

class IslandoraTuque {

  /**
   * The repository object.
   *
   * @var FedoraRepository
   */
  public $repository = NULL;

  /**
   * Constructor.
   *
   * @param array $user
   *   A Drupal user.
   * @param string $url
   *   The url to the fedora instance.
   */
  public function __construct($user = NULL, $url = NULL) {
    module_load_include('inc', 'islandora', 'includes/tuque_wrapper.inc');
    if (!isset($user)) {
      global $user;
    }

    if ($user->uid == 0) {
      $user_string = 'anonymous';
      $pass_string = 'anonymous';
    }
    else {
      $user_string = $user->name;
      $pass_string = $user->pass;
    }

    if (!isset($url)) {
      $url = variable_get('islandora_base_url', 'http://localhost:8080/fedora');
    }

    if (self::exists()) {
      $config = new Tuque\RepositoryConfig($url, $user_string, $pass_string);
      $this->repository = new IslandoraFedoraRepository($config);
    }
  }

  /**
   * Checks if the Connection class exists.
   *
   * @todo Can we get rid of this?
   *
   * @returns bool
   *   TRUE if the Connection class exists FALSE otherwise.
   */
  public static function exists() {
    module_load_include('inc', 'islandora', 'includes/tuque_wrapper.inc');
    return class_exists('Tuque\Repository');
  }

  /**
   * Displays and error for use when Tuque is not installed.
   */
  public static function getError() {
    $islandora_doc_link = l(t('Islandora documentation'), 'https://wiki.duraspace.org/display/ISLANDORA/Islandora');
    $tuque_link = l(t('Tuque Fedora API'), 'http://github.com/islandora/tuque');
    $message = t('Islandora requires the !tuque_url. Please install in /sites/all/libraries/tuque before continuing. See the !islandora_url.', array('!tuque_url' => $tuque_link, '!islandora_url' => $islandora_doc_link));
    drupal_set_message(filter_xss($message), 'error', FALSE);
  }
}
