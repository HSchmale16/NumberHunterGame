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
			<h1>Get The Game</h1>
			<p>This game is available as source code and a binary release. The source code
               may be found at <a href="http://adf.ly/wY8l7">http://adf.ly/wY8l7</a>.
               A binary release may be found at <a href="http://adf.ly/1FMxPi">
               http://adf.ly/1FMxPi</a>.</p>
			
			<!-- Available Downloads Table -->
			<h2>Available Downloads</h2>
			<table id="AvailDownloads">
				<tr>
					<th>Release Target</th>
					<th>Link</th>
				</tr>
				<tr> <!-- Source Code Link -->
					<td>Source Code</td>
					<td><a href="http://adf.ly/wY8l7">Adfly Link to github</a></td>
				</tr>
				<tr><!-- Windows Binary Release -->
					<td>Windows Binary Release <br/>
					This is a zip archive.</td>
					<td><a href="http://adf.ly/1FMxPi">Release Github</a></td>
				</tr>
			</table>
		</div><!-- close main-content -->
		
		<?
			include("Includes/Footer.php");
		?>
	</div><!-- close page-container -->
</body>
</html>
