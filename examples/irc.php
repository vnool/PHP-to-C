<?php
	$sock = socket_create(AF_INET, SOCK_STREAM, 0);
	$connection = socket_connect($sock, 'irc.freenode.net', 6667);

	socket_write($sock, "USER TestBOT TestBOT TestBOT :TestBOT\r\n");
	socket_write($sock, "NICK TestBOT \r\n");
	socket_write($sock,"JOIN #binaryphp \r\n");
	while ($data = socket_read($sock, 2048))
	{
		$temp = explode(':', $data);
		$temp2 = explode('!', $temp[1]);
		$temp3 = explode(' ', $temp2[1], 4);
		$nick = $temp2[0];
		$act = $temp3[1];
		$recp = $temp3[2];
		if($act == 'PRIVMSG')
		{
			echo '<', $nick, '> ', trim($temp[2]), "\n";
			$bleh = explode(' ', trim($temp[2]));
			if($bleh[0] == '+punch')
				socket_write($sock, 'PRIVMSG ' . $recp . ' :' . "\x01" . 'ACTION punches ' . $bleh[1] . ' in the face.' . "\x01\r\n");
		}
	}
?>
