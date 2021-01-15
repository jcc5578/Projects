

<?php
	header("Content-type: text/css; charset: UTF-8"); 
	//require '../index.php';

	//$colorBlind = $_POST["colorBlind"];
	//if (strcmp($colorBlind, "normal") == 0){
		if(!session_id()) session_start();
			$colorBlind = $_SESSION['colorBlind'];
		if(!isset($_SESSION['colorBlind'])) {
			$color = "#1DB954";
		} else if (strcmp($colorBlind, "normal") == 0){
			$color = "#1DB954";
		} else if (strcmp($colorBlind, "protanopia") == 0){
			$color = "#B815C9";
		} else if (strcmp($colorBlind, "deuteranopia") == 0){
			$color = "#327EE4";
		} else if (strcmp($colorBlind, "tritanopia") == 0){
			$color = "#32D6E4";
		}
	//}
?>

@import url(//fonts.googleapis.com/css?family=Titillium+Web);

*{
  font-family:'Titillium Web', sans-serif;
}


body {
  max-width: 900px;
  min-width: 100px;
  margin: auto;
  width: 50%;
  border: auto solid green;
  padding: 10px;
  background-color: #FFFFFF;
  color: black;
}

.center {
  margin: ;
  width: 50%;
  border: px solid green;
  background-color: #FFFFFF;
  padding: 10px;
}

.buttonHolder {
	background-color: <?php echo $color ?>;
	font-size: 0px;
	width: 100%;
}

.button {
  border: none <?php echo $color ?>;
  color: black;
  padding: 12px 24px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 18px;
  margin: 4px 2px <?php echo $color ?>;
  transition-duration: 0.4s;
  cursor: pointer;
}

.contact {
  border: solid 2px <?php echo $color ?>;
  color: black;
  padding: 10px 16px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 20px;
  margin: 4px 2px <?php echo $color ?>;
  
  max-width: 50%;
  float:right;
}

.currentButton {
  background-color: <?php echo $color ?>;
  color: white;
}

.button:hover {
  background-color: <?php echo $color ?>;
  color: white;
}

.thumbnail {
    display:block;
    /* set width to 100%  */
    max-width: 100%; 
    height: auto;
    width: auto;
}

.thumbnail2 {
    display:block;
    /* set width to 33%  */
    max-width: 40%; 
    height: auto;
    width: auto;
}

.thumbnail3 {
    display:block;
    /* set width to 33%  */
    max-width: 50%; 
    height: auto;
    width: auto;
}

.row {
  width: 800px
  display: flex;
}

.column {
  flex-basis: 300px;
  padding: 0px;
}

.tts-text {
	font-size: 0px;
}

.recrow {
  display: flex;
}

.reccolumn {
  flex: 50%;
}

.music {
	height: 440px;
	max-width: 90%;
}

a.external {
    background: url(/content/External.png) center right no-repeat;
    padding-right: 13px;
}

}