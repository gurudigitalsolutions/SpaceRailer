<?php
////////////////////////////////////////////////////////////////////////////////
//
//	map-tilesplit.php
//
//	This script is meant to help split an image into multiple tiles.
//
//	Written by Brian Murphy, 2022
//
////////////////////////////////////////////////////////////////////////////////

$imgFile = '../resources/backdrops/eta_caranae/eta_caranae_nebula.png';
$tileDir = '../resources/backdrops/eta_caranae/';

$imageWidth = 1024;
$imageHeight = 512;

$tileWidth = 32;
$tileHeight = 32;

$source_image = new Imagick($imgFile);

for($w = 0; $w < ($imageWidth / $tileWidth); $w++)
{
	for($h = 0; $h < ($imageHeight / $tileHeight); $h++)
	{
		$x = $w * $tileWidth;
		$y = $h * $tileHeight;
		
		$image = clone $source_image;
		$image->cropImage($tileWidth, $tileHeight, $x, $y);
		$image->writeImage($tileDir.'tile_'.$w.'_'.$h.'.png');
	}
}
