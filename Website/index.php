<!-- index.php
--	Main page for game, displays news
--	December 8, 2014
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
			<?php
				// News Post
				$tbName = getNews_Tb_Name();
				$sql = "Select POSTER, DTPOSTED, TITLE, BODY FROM $tbName ORDER BY DTPOSTED DESC LIMIT 5;";
				$result = $dbConn->query($sql);
				if($result->num_rows > 0)
				{
					while($row = $result->fetch_assoc())
					{
						echo "<h1>".$row["TITLE"]."</h1>\n";
						echo $row["BODY"];
						echo "<p class=\"author\">" . $row["POSTER"];
                        echo " on " . $row['DTPOSTED'] . "</p>";
					}
				}
				else
				{
					echo "<h1>No News Posts Available</h1>\n";
				}
			?>
		</div><!-- close main-content -->
		
		<?
			include("Includes/Footer.php");
		?>
	</div><!-- close page-container -->
</body>
</html>
