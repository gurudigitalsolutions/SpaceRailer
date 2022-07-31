<?php
////////////////////////////////////////////////////////////////////////////////
//
//	map-generate.php
//
//	Generate a barebones map for development and testing.
//	https://github.com/gurudigitalsolutions/SpaceRailer/wiki/Map-Format
//
//	Written by Brian Murphy, 2022
//
////////////////////////////////////////////////////////////////////////////////

$mapFile = 'map.srm';
$mapTitle = 'Testlands';

$fh = fopen($mapFile, 'wb');

//	Write an appropriate header
//	This includes the string 'SRMF' and the map version number.  Note that the
//	map version has the least significant byte first.
fwrite($fh, 'SRMF');
fwrite($fh, chr(0x0001));
fwrite($fh, chr(0x0000));

//	Now to write the layer sizes.  There are four layers, starting with the
//	closest layer to the screen.  The second layer is the layer that the player
//	is actually on.

//	Foreground (2048 * 2048)
fwrite($fh, chr(0x00));
fwrite($fh, chr(0x08));

fwrite($fh, chr(0x00));
fwrite($fh, chr(0x08));

//	Active (1024 * 1024)
fwrite($fh, chr(0x00));
fwrite($fh, chr(0x04));

fwrite($fh, chr(0x00));
fwrite($fh, chr(0x04));

//	Background (128 * 128)
fwrite($fh, chr(0x00));
fwrite($fh, chr(0x01));

fwrite($fh, chr(0x00));
fwrite($fh, chr(0x01));

//	Backdrop (64 * 64)
fwrite($fh, chr(0x40));
fwrite($fh, chr(0x00));

fwrite($fh, chr(0x40));
fwrite($fh, chr(0x00));

//	Write a title, then pad the 32 byte space with nulls
fwrite($fh, $mapTitle);

for($eb = strlen($mapTitle); $eb < 32; $eb++)
{
	fwrite($fh, chr(0x00));
}

//	Fill the rest with 0 for no flags
for($eb = 0x0036; $eb < 0x0080; $eb++)
{
	fwrite($fh, chr(0x00));
}

//	Define a few sprites
fwrite($fh, 'images/linus_guard1.png');
fwrite($fh, chr(0x00));

fwrite($fh, 'images/enemy-1-rip-1.png');
fwrite($fh, chr(0x00));

fwrite($fh, 'images/power-up.png');
fwrite($fh, chr(0x00));

//	Define the nebula tiles
for($ey = 0; $ey < 16; $ey++)
{
	for($ex = 0; $ex < 32; $ex++)
	{
		fwrite($fh, 'backdrops/eta_caranae/tile_'.$ex.'_'.$ey.'.png');
		fwrite($fh, chr(0x00));
	}
}

fwrite($fh, chr(0x00));

//	Now to add some map data.  This is each layer of the map.
//	Foreground - no tiles present yet
for($ey = 0; $ey < 2048; $ey++)
{
	for($ex = 0; $ex < 2048; $ex++)
	{
		//	Write 4 bytes - tile id, followed by flags
		fwrite($fh, chr(0x00));
		fwrite($fh, chr(0x00));
		fwrite($fh, chr(0x00));
		fwrite($fh, chr(0x00));
	}
}

//	Active, some random power up icons
for($ey = 0; $ey < 1024; $ey++)
{
	for($ex = 0; $ex < 1024; $ex++)
	{
		if($ex % 9 == 0
		&& $ey % 6 == 0)
		{
			fwrite($fh, chr(0x03));
		}
		else
		{
			fwrite($fh, chr(0x00));
		}
		
		fwrite($fh, chr(0x00)); // Most significant byte
		fwrite($fh, chr(0x00)); // Flags
		fwrite($fh, chr(0x00)); 
	}
}

//	Background, evenly spaced nebulas
for($ey = 0; $ey < 256; $ey++)
{
	for($ex = 0; $ex < 256; $ex++)
	{
		$tileID = ($ex % 32) + (($ey % 16) * 32);
		$tileID += 4;
		echo "Writing tile ID: x: ".$ex.", y:".$ey." id:".$tileID."\n";
		
		fwrite($fh, chr(0xFF & $tileID));
		fwrite($fh, chr((0xFF00 & $tileID) >> 8));
		
		fwrite($fh, chr(0x00)); // Flags
		fwrite($fh, chr(0x00)); 
	}
}

//	Backdrop, nothing for now
for($ey = 0; $ey < 64; $ey++)
{
	for($ex = 0; $ex < 64; $ex++)
	{
		//	Write 4 bytes - tile id, followed by flags
		fwrite($fh, chr(0x00));
		fwrite($fh, chr(0x00));
		fwrite($fh, chr(0x00));
		fwrite($fh, chr(0x00));
	}
}

//	The footer does not need any information at this point in time.

fclose($fh);
