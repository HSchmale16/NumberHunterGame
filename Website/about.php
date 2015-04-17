<!-- about.php
--	About page for game
--	December 8, 2014
-->

<?php
	include_once("Includes/connectDB.php");
?>

<html>
<head>
	<title>Number Hunter Game</title>
	<LINK REL=StyleSheet HREF="/Style/MainStyle.css" TYPE="text/css" />
    <LINK REL=StyleSheet HREF="/Style/generic.css" TYPE="text/css" />
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
			<h1>About Number Hunter</h1>
			<p>Number Hunter is about building number recognition skills in early childhood.
			It helps children learn to differintate between several types of numbers
			such as prime, even or odd.</p>
			
			<p>This game is open sourced with the intent for people to learn from
			the code. It is requested that you visit this
			<a href="http://numberhuntergame.com/getGame.php">page</a> to download the
			game. It is requested that you submit all changes you make to the github
			available at the page metioned above. However, you are free to distribute
			the changes you make as source code, so long as you don't change or remove
			the credits screen.</p>

			<h2>The Storyline</h2>
			<p>It was the dawn of the 7th age of mankind, the year is 3072. Just after the great cataclysm left most developed species planet-bound, however mankind is beginning to rebuild and get back into space using the remains of the forerunners. You are a captain of a small salvage ship helping to rebuild The Great Terran Empire from the ashes of our predecessors.</p>
		
			<h2>Credits</h2>
			<ul>
				<li>Programmed By: Henry J Schmale</li>
				<li>Art by: Anon</li>
				<li>Sound from: <a href="Soundbible.com">Soundbible.com</a></li>
				<li>Music From: <a href="http://incompetech.com/">http://incompetech.com/</a></li>
				<ul>
					<li>"Ready Aim Fire"
						Kevin MacLeod (incompetech.com)
						Licensed under Creative Commons: By Attribution 3.0
						http://creativecommons.org/licenses/by/3.0/</li>
					<li>"Space Fighter Loop"
						Kevin MacLeod (incompetech.com)
						Licensed under Creative Commons: By Attribution 3.0
						http://creativecommons.org/licenses/by/3.0/</li>
				</ul>
			</ul>
		</div><!-- close main-content -->
		
		<?
			include("Includes/Footer.php");
		?>
	</div><!-- close page-container -->
</body>
</html>
