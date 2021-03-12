/**
 * The target website likely has a PHP script similar to this.
 * Only accepts PHP files and searches for them in /var/www/html/
 */ 
<?php
$file = $_GET['view'];
include "http://IP/?view=" . $file . ".php"
}
?>
