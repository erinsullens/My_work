<?php
DEFINE ('DB_USER', 'sullense-db');
DEFINE ('DB_PASS', '70DPvzyzc4bSHk8k');
DEFINE ('DB_HOST', 'oniddb.cws.oregonstate.edu');
DEFINE ('DB_NAME', 'sullense-db');

$dbc = @mysqli_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME)
    OR die('Could not connect to MySQL: ' .
mysqli_connect_error());

?>