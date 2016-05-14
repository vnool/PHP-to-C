<?php
$fruits = array('d' => 'lemon',
		'a' => 'orange',
		'b' => 'banana',
		'c' => 'apple');
ksort ($fruits);
echo implode("\n", $fruits);
?>
