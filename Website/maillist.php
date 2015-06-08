<!-- maillist.php
Sign up for the mailing list
-->
<?php
include_once("Includes/connectDB.php");
?>

<html>
<head>
	<title>Mailing List - Number Hunter Game</title>
	<LINK REL=StyleSheet HREF="/Style/MainStyle.css" TYPE="text/css" MEDIA=screen>
    <link rel="icon"
          type="image/ico"
          href="favicon.ico" />
</head>

<body>
<div id="page-container">
	<div id="header">
		<img src="Img/header.jpg" alt="header.jpg"/>
	</div><!-- close header -->
		
	<div id="navbar">
		<ul>
			<li><a href="/index.php">Home</a></li>
	   		<li><a href="/about.php">About</a></li>
			<li><a href="/getGame.php">Get The Game</a></li>
			<li><a href="/highscores.php?Level=1&diff=0">HighScores</a></li>
			<li class="last"><a href="/support.php">Support</a></li>
		</ul>
	</div><!-- close navbar -->
	
	<!-- Begin Main-Content -->
	<div id="main-content">
    <h1>Sign up for the mailing list</h1>
    <strong>Coming Soon!</strong>
    <p>This game has a mailing list now.</p>
	</div><!-- close main-content -->
	
	<?
	include("Includes/Footer.php");
	?>
</div><!-- close page-container -->
</body>
</html>
