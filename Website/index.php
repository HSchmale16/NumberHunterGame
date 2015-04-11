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
				$sql = "Select POSTER, DATE, TITLE, BODY FROM $tbName ORDER BY ID DESC LIMIT 10;";
				$result = $dbConn->query($sql);
				if($result->num_rows > 0)
				{
					while($row = $result->fetch_assoc())
					{
						echo "<h1>".$row["TITLE"]."</h1>\n";
						echo "<pre class=\"news\">" . $row["BODY"] . "</pre>";
						echo "<p class=\"author\">-" . $row["POSTER"] . "</p>";
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