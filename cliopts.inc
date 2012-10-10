<?php

class CliOpt
{
  /**
   * Cli options
   *
   * @var array
   */
  private static $argv = array();

  /**
   * Option name
   *
   * @var string
   */
  public $name;
  /**
   * Value type
   *
   * @var string
   */
  public $type;
  /**
   * Description for help
   *
   * @var string
   */
  public $desc;
  /**
   * Is option mandatory?
   *
   * @var boolean
   */
  public $optional = true;
  /**
   *
   * New object
   *
   * @param string $name
   * @param string $type
   * @param boolean $optional
   * @param string $desc
   */
  public function __construct($name, $type = null, $desc = '', $optional = true)
  {
    $this->name = $name;
    $this->type = $type;
    $this->desc = $desc;
    $this->optional = $optional ? true : false;
  }
  public static function initArgv($argv)
  {
    self::$argv = $argv;
  }
  /**
   *
   * Validate and cast option value
   *
   * @param mixed $value
   * @throws Exception
   * @return mixed
   */
  public function validate($value)
  {
    if ($this->optional && !$value)
    {
      return true;
    }

    if (!$this->optional && !$value)
    {
      throw new Exception("  Parameter {$this->name} value must be set");
    }

    switch ($this->type)
    {
      case 'int':
        if (strval($value) != strval(intval($value)))
        {
          throw new Exception("Parameter {$this->name} value must be integer");
        }
        return intval($value);
      case 'date':
        if ($value != date('Y-m-d', strtotime($value)))
        {
          throw new Exception("Parameter {$this->name} value must be date with format Y-m-d");
        }
        return $value;
      default:
        return $value;
    }
  }
  /**
   *
   * Get option position in $argv
   *
   * return integer
   */
  private function getPos()
  {
    $pos = array_search($this->name, self::$argv);
    if ($pos === false)
    {
      $pos = array_search('-' . $this->name, self::$argv);
    }
    return $pos;
  }
  /**
   *
   * Check that option exists
   *
   * @return boolean
   */
  public function exists()
  {
    return $this->getPos() !== false;
  }
  /**
   *
   * Get value
   *
   * @return mixed
   */
  public function getValue()
  {
    $pos = $this->getPos();
    if ($pos !== false || !$this->optional)
    {
      return $this->validate(self::$argv[$pos + 1]);
    }
    return null;
  }
}

class CliOpts
{
  /**
   *
   * @var array[CliOpt]
   */
  private static $opts = array();
  /**
   *
   * Init options
   *
   */
  public static function init(/* CliOpt, CliOpt, ... */)
  {
    self::$opts['help'] = new CliOpt('help', null, 'Show help');
    foreach (func_get_args() as $p)
    {
      self::addOpt($p);
    }
  }
  /**
   *
   * Comment
   *
   * @param CliOpt
   */
  public static function setParams(/* CliOpt, CliOpt, ... */)
  {
    foreach (func_get_args() as $p)
    {
      self::addOpt($p);
    }

    if (self::get('help'))
    {
      self::showHelp();
    }

    try
    {
      foreach (self::$opts as $p)
      {
        /* @var $p CliOpt */
        $p->getValue();
      }
    }
    catch (Exception $e)
    {
      echo $e->getMessage()."\n";
      self::showHelp();
      exit;
    }
  }
  /**
   *
   * Add new option
   *
   * @param CliOpt $p
   */
  public static function addOpt(CliOpt $p)
  {
    self::$opts[$p->name] = $p;
  }
  /**
   *
   * Get option
   *
   * @param string $name Option name
   * @return CliOpt
   */
  public static function getOpt($name)
  {
    if (self::$opts[$name])
    {
      return self::$opts[$name];
    }
    return new CliOpt($name);
  }
  /**
   *
   * Show help
   *
   */
  public static function showHelp()
  {
    foreach (self::$opts as $p)
    {
      /* @var $p CliOpt */
      echo "\t".$p->name . ($p->type ? ' (' . $p->type . ')' : '') .($p->optional ? ' [optional]' : '').' '.$p->desc . "\n";
    }
    exit;
  }
  /**
   *
   * Print out options values
   *
   */
  public static function showValues()
  {
    foreach (self::$opts as $p)
    {
      /* @var $p CliOpt */
      echo $p->name . ': '.$p->getValue() . "\n";
    }
  }
  /**
   *
   * Get option
   *
   * @param string $o Option name
   * @return mixed Value of option
   */
  public static function get($o)
  {
    return self::getOpt($o)->getValue();
  }
}

CliOpt::initArgv($argv);

