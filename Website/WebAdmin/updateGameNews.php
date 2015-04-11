<?php
	// Game News Update Script
	// Updates the game news on the homepage
	// this is an admin only script
	include_once("../Includes/connectDB.php");

	$uname = $_POST["poster"];
	$pwd = $_POST["password"];
	$title = $_POST["title"];
	$content = $_POST["body"];
	
	// Insert News Post
	$tbName = getNews_Tb_Name();
	if($dbConn->query("Insert into $tbName(DATE, POSTER, TITLE, BODY) VALUES (NOW(), \"$uname\", \"$title\", \"$content\");") === FALSE)
	{
		die("FAIL!" . $dbConn->error);
	}
	
?>
