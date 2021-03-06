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

//	Background (512 * 512)
fwrite($fh, chr(0x00));
fwrite($fh, chr(0x02));

fwrite($fh, chr(0x00));
fwrite($fh, chr(0x02));

//	Backdrop (256 * 256)
fwrite($fh, chr(0x00));
fwrite($fh, chr(0x01));

fwrite($fh, chr(0x00));
fwrite($fh, chr(0x01));

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

fwrite($fh, 'backdrops/Eta_Carinae_Nebula.png');
fwrite($fh, chr(0x00));

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

//	Active, random sprites but mostly nothing
for($ey = 0; $ey < 1024; $ey++)
{
	for($ex = 0; $ex < 1024; $ex++)
	{
		$randTile = rand(0, 10);
		if($randTile == 0) { fwrite($fh, chr(0x01)); }
		elseif($randTile == 1) { fwrite($fh, chr(0x02)); }
		else if($randTile == 2) { fwrite($fh, chr(0x03)); }
		else { fwrite($fh, chr(0x00)); }
		
		fwrite($fh, chr(0x00)); // Most significant byte
		fwrite($fh, chr(0x00)); // Flags
		fwrite($fh, chr(0x00)); 
	}
}

//	Background, random sprites
for($ey = 0; $ey < 512; $ey++)
{
	for($ex = 0; $ex < 512; $ex++)
	{
		$randTile = rand(1, 3);
		if($randTile == 1) { fwrite($fh, chr(0x01)); }
		elseif($randTile == 2) { fwrite($fh, chr(0x02)); }
		else { fwrite($fh, chr(0x03)); }
		
		fwrite($fh, chr(0x00)); // Most significant byte
		fwrite($fh, chr(0x00)); // Flags
		fwrite($fh, chr(0x00)); 
	}
}

//	Backdrop, nothing for now
for($ey = 0; $ey < 256; $ey++)
{
	for($ex = 0; $ex < 256; $ex++)
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
