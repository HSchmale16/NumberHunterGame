<!-- tos.php
     Website Terms of Service
	 December 8, 2014
-->
<?php
	include_once("Includes/connectDB.php");
?>

<html>
<head>
	<title>Number Hunter Game</title>
	<LINK REL=StyleSheet HREF="/Style/MainStyle.css" TYPE="text/css" MEDIA=screen>
    <link rel="icon"
          type="image/ico"
          href="favicon.ico" />
    <meta name="msvalidate.01" content="975F95807D670C15E30D60749AD6F6F1" />
    <meta name="google-site-verification" content="Aqr6pwcYBsizFVN2b2g_UtUou53qoDpJoqKSU488d-0" />
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
        <h1>Terms of Service</h1>
        <p>This page states the terms of service for this game. These rules
           are meant to encourge fair play of the game, and foster
           competition between players.</p>
        <ol>
            <li>This game may collect information about the players. Possible
                information collected includes the score gotten and general
                gameplay statistics, this is only logged if submitting to the
                high scores server is enabled.</li>
            <li>You may not attempt to hack the server.</li>
            <li>You may not cheat or attempt to upload scores that were gained
                by using nonoffical config files.</li>
            <li>Offical config files are defined as any set of config files
                available in the git repo.</li>
        </ol>
		</div><!-- close main-content -->
		
		<?
		include("Includes/Footer.php");
		?>
	</div><!-- close page-container -->
</body>
</html>
