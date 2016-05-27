<?php
/**
 * @file
 * Plugin to provide access control/visibility based on date and time.
 */
class DateTimeLayoutAccess extends LayoutAccessNegatable {

  /**
   * {@inheritdoc}
   */
  function summary() {
    $start = format_date(strtotime($this->settings['start_time']),'medium');
    $end = format_date(strtotime($this->settings['end_time']),'medium');
    if ($this->settings['negate']) {
      return t('Date is NOT: from @start to @end', array('@start'  => $start, '@end' => $end));
    }
    else {
      if (!empty($start) && !empty($end)) {
        return t('Date is: from @start to @end', array('@start'  => $start, '@end' => $end));
      }
      elseif (empty($start)) {
        return t('Date is before @end', array('@end' => $end));
      }
      elseif (empty($end)) {
        return t('Date is after @start', array('@start' => $start));
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  function checkAccess() {
    $timezone = '';
    if ($this->settings['timezone'] == 'user') {
      $timezone = ' ' . backdrop_get_user_timezone();
    }
    $start = !empty($this->settings['start_time']) ? strtotime($this->settings['start_time'] . $timezone) : NULL;
    $end = !empty($this->settings['end_time']) ? strtotime($this->settings['end_time'] . $timezone) : NULL;
    $now = time();

    // If a range was given, return true during the range, but if negated,
    // return false.
    if ($start && $end) {
      $in_range = (($start < $now) && ($end > $now));
      return $this->settings['negate'] ? !$in_range : $in_range;
    }
    // If only an end time was given return true only before the end time has
    // passed.
    elseif (!$start) {
      return ($now < $end);
    }
    // If only a start time was given, return true after the start time.
    elseif (!$end) {
      return ($now > $start);
    }
  }

  /**
   * {@inheritdoc}
   */
  function form(&$form, &$form_state) {
    parent::form($form, $form_state);

    $now = format_date(time(),'medium');
    $format = 'Y-m-d H:i';
     
    $form['start_time'] = array(
      '#type' => 'date_popup',
      '#date_format' => $format,
      '#title' => t('Start time'),
      '#date_label_position' => 'invisible',
      '#date_year_range' => '-0:+3',
      '#default_value' => isset($this->settings['start_time']) ? $this->settings['start_time'] : '',
    );
    $form['end_time'] = array(
      '#type' => 'date_popup',
      '#date_format' => $format,
      '#title' => t('End time'),
      '#date_label_position' => 'invisible',
      '#date_year_range' => '-0:+3',
      '#default_value' => isset($this->settings['end_time']) ? $this->settings['end_time'] : '',
    );
    $form['timezone'] = array(
      '#type' => 'radios',
      '#title' => t('Timezone'),
      '#description' => t("If set to 'User', access will be determined based on the time in the user's timezone, not the site time. Current site time is !now", array('!now' => $now)),
      '#options' => array(
        'site' => t('Site'),
        'user' => t('User'),
      ),
      '#default_value' => isset($this->settings['timezone']) ? $this->settings['timezone'] : 'site',
    );
  }
}


  /**
   * {@inheritdoc}
   */
  function formValidate($form, &$form_state) {
    // At least one time option must be supplied.
    if (empty($form_state['start_time']) && empty($form_state['end_time'])) {
      form_set_error('end_time', t('At least one time range must be provided.'));
    }
    // Negate only works on ranges.
    if ($form_state['negate'] && (empty($form_state['start_time']) || empty($form_state['end_time']))) {
      form_set_error('negate', t('A full time range must be provided to use the negate option.'));
    }
  }
