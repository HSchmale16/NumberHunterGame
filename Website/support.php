<!-- support.php
--	Support page for game, offers contact information and FAQ's
--	December 8, 2014
-->

<?php
	include_once("Includes/connectDB.php");
?>

<html>
<head>
	<title>Number Hunter Game</title>
	<LINK REL=StyleSheet HREF="/Style/MainStyle.css" TYPE="text/css" MEDIA=screen>
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
			<h1>Support</h1>
			<p>For assistance with the website please email: <a href="mailto:webmaster@numberhuntergame.hostyd.net">webmaster@numberhuntergame.hostyd.net</a></p>
			<p>For assistance with the game please email: <a href="mailto:gamesupport@numberhuntergame.hostyd.net">gamesupport@numberhuntergame.hostyd.net</a></p>
		</div><!-- close main-content -->
		
		<?
			include("Includes/Footer.php");
		?>
	</div><!-- close page-container -->
</body>
</html>