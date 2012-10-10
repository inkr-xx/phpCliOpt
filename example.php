<?php
require_once 'cliopts.inc';

/**
 * Define some misc options
 */
CliOpts::init(
  new CliOpt('debug', 'bool', 'Show debugging data')
);

if (CliOpts::get('debug'))
{
  /**
   * Start debugging etc
   */
}

/**
 * Set script specific options and validate options
 */

CliOpts::setParams(
  new CliOpt('id', 'int', 'Object ID', false), // Mandatory
  new CliOpt('d', 'date', 'Time to last trip'), // Optional
  new CliOpt('e', null, 'Email to send result') // Optional
);


CliOpts::showValues();

?>