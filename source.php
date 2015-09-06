<?php
/*
 Server-Sent Events / EventSource DEMO
 Claudius Coenen

 This is free software. Use, modify and tinker with it however you like!
 LICENSED UNDER CC-BY-4.0 http://creativecommons.org/licenses/by/4.0/
 */

error_log('script starting');
header('Content-Type: text/event-stream');
header('Access-Control-Allow-Origin: *');
header('Cache-Control: no-cache');

echo "retry: 3000\n";

$seed = rand();
$count = 0;


function sendMsg($msg) {
	global $count, $seed;
	error_log('messaege sent: ' . $msg);
	echo "event: testeventcc\n";
	echo "data: $msg $count $seed\n\n";
	ob_flush();
	flush();
}


while (!connection_aborted()) {
	$count++;
	sendMsg('server time: ' . date("H:i:s"));
	usleep(16000); // 16ms per message -> 60msg/s
}
error_log("connection closed");
