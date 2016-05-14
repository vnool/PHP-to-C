<?php
$sock = socket_create(AF_INET, SOCK_STREAM, 0);
$connection = socket_connect($sock, 'irc.freenode.net', 6667);

socket_write($sock, "USER TestBOT TestBOT TestBOT :TestBOT\r\n");
socket_write($sock, "NICK TestBOT \r\n");
socket_write($sock,"JOIN #binaryphp \r\n");
while ($data = socket_read($sock, 2046))
{
	echo $data, "\n";
	$temp = explode(':', $data);
	$temp2 = explode('!', $temp[1]);
	$temp3 = explode(' ', $temp2[1]);
	if(strpos('TestBOT: PING?', $temp[2]) !== false)
		socket_write($sock, 'PRIVMSG ' . $temp3[2] . ' :' . $temp2[0] . ": PONG!\r\n");

	if(strpos('!quit', $temp[2]) !== false)
	{
		if($temp2[0] == 'Amaranth')
			socket_write($sock, 'QUIT :Seeya ' . $temp3[2] . "\r\n");
	}
}
?>