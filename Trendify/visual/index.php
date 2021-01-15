<!-- Homepage -->

<!DOCTYPE html>
<html lang="en-US"> 

		
	<?php 
			if (isset($_COOKIE["poorSight"])){
			$poorSight = $_COOKIE["poorSight"];
			$colorBlind = $_COOKIE["colorBlind"];
		} else if (!isset($poorSight)){
			$poorSight = "no";
			$colorBlind = "normal";
		}
		
		$red = "#FF0000";
		$green = "#319400";
		$blue = "#0062FF";
		
		global $red;
		global $green;
		global $blue;
		
		if (strcmp($colorBlind, "protanopia") == 0){
			$green = "#13FF17";
			} else if (strcmp($colorBlind, "deuteranopia") == 0){
			$red = "#6D0B42";
			} else if (strcmp($colorBlind, "tritanopia") == 0){
			$blue = "#7A2088";
		}
	?>
	<head>
		<meta charset="UTF-8">
		
		<link rel="stylesheet" href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css">
		<link rel="stylesheet" type="text/css" href="../content/style.php" media="screen"></link>
		
		<center>
			<a href="index.html" rel="home">
			</a></center>
			
			<!--<body bgcolor = "#1DB954">style="font-size:0px"-->
			<center>
				<div class = buttonHolder>
					<a href="../index.php"> <button class = "button">[Home]</button></a>
					<a href="../recommender/index.php"> <button class = "button">[Music Recommender]</button></a>
					<a href="../visual/index.php"> <button class = "button currentButton">[Taste Visualizer]</button></a>
					<a href="../bands/index.php"> <button class = "button">[Nearby Bands]</button></a>
					<!--<a href="accom/index.html"> <button class = "button">[Accommodation]</button></a-->
				</div></center>
	</body>
	
</div></div>
    <style type="text/css">
        #login, #loggedin {
            display: none;
        }
        .text-overflow {
            overflow: hidden;
            text-overflow: ellipsis;
            white-space: nowrap;
            width: 800px;
        }
        </style>
    </head>

    <body>
        <div>
        <div id="login">
        <center>
            <h3>Please login in order to allow our app to make the taste graphs.</h3>
            <p class = "tts-text" id = "tts-text"> </p>
            <button id="login-button" class="btn btn-primary">Log in with Spotify</button>
            </center>
        </div>
        <div id="loggedin">
            <div id="user-profile">
            </div>
            <div id="user-short-song">
            </div>
            <div id="user-long-song">
            </div>
            <div id="oauth">
            </div>
        </div>
        </div>
    </body>
    
    <script id="user-profile-template" type="text/x-handlebars-template">
	<body>
      <h1>Logged in as {{display_name}}</h1>
      <div class="media">
        <div class="pull-left">
          <img class="media-object" width="150" src="{{images.0.url}}" />
        </div>	
        <div class="media-body">
          <dl class="dl-horizontal">
            <dt>Display name</dt><dd class="clearfix">{{display_name}}</dd>
            <dt>Id</dt><dd>{{id}}</dd>
            <dt>Email</dt><dd>{{email}}</dd>
            <dt>Spotify URI</dt><dd><a href="{{external_urls.spotify}}">{{external_urls.spotify}}</a></dd>
            <dt>Link</dt><dd><a href="{{href}}">{{href}}</a></dd>
            <!--<dt>Profile Image</dt><dd class="clearfix"><a href="{{images.0.url}}">{{images.0.url}}</a></dd>-->
            <dt>Country</dt><dd>{{country}}</dd>
          </dl>
        </div>
      </div>
	  <hr align = "left" style = "background-color:black;height:2px">
	  </body>
    </script>	

    <script id="oauth-template" type="text/x-handlebars-template">
      <h2>oAuth info</h2>
      <dl class="dl-horizontal">
        <dt>Access token</dt><dd class="text-overflow">{{access_token}}</dd>
      </dl>
    </script>

    <script src="//cdnjs.cloudflare.com/ajax/libs/handlebars.js/2.0.0-alpha.1/handlebars.min.js"></script>
    <script src="http://code.jquery.com/jquery-1.10.1.min.js"></script>
    <script>
      (function() {

        var stateKey = 'spotify_auth_state';

        /**
         * Obtains parameters from the hash of the URL
         * @return Object
         */
        function getHashParams() {
          var hashParams = {};
          var e, r = /([^&;=]+)=?([^&;]*)/g,
              q = window.location.hash.substring(1);
          while ( e = r.exec(q)) {
             hashParams[e[1]] = decodeURIComponent(e[2]);
          }
          return hashParams;
        }

        /**
         * Generates a random string containing numbers and letters
         * @param  {number} length The length of the string
         * @return {string} The generated string
         */
        function generateRandomString(length) {
          var text = '';
          var possible = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';

          for (var i = 0; i < length; i++) {
            text += possible.charAt(Math.floor(Math.random() * possible.length));
          }
          return text;
        };
        function flot_graph_short (array)
        {
            console.log("short");
            console.log(array);
            var maxarray = [];
            var data2 = [];
            var ticks = [];
            var inilength = 6;
            if (inilength > array.length)
                inilength = array.length;
            for (var i = 0; i < inilength; i++)
            {
                var max = 0;
                var name = "";
                for (var j = 0; j < array.length; j++)
                {
                    if (array[j][1] > max)
                    {
                        max = array[j][1];
                        name = array[j][0];
                        array[j][1] = parseInt(0);
                    }
                }
                maxarray.push([name, parseInt(max)]);
                data2.push([parseInt(i), maxarray[i][1]]);
                ticks.push([parseInt(i), maxarray[i][0]]);

            }
            var outputlist = maxarray[1][0];
            for (var x = 2; x < maxarray.length-1; x++)
            {
                outputlist += ", " + maxarray[x][0];
            }
            document.getElementById("tts-text").innerHTML += "Your most listened to genre in the long term is: " + maxarray[0][0] + ", followed by " + outputlist + ", and " + maxarray[maxarray.length-1][0] + " \n ";
            var dataset2 = [
                {
                    label: "Total Count", data: data2, color: "#5482FF"
                }
            ];
            var options = {
                series: {
                    bars: {
                        show: true,
                        align: "center",
                        barWidth: 0.5
                    }
                },
                xaxis: {
                    axisLabel: "Genres",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 10,
                    ticks: ticks
                },
                yaxis: {
                    axisLabel: "Total Count",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 3,
                },
                grid: {
                    hoverable: true,
                    borderWidth: 2,
                    backgroundColor: {colors: ["#ffffff", "#EDF5FF"]}
                }
            };

            $(document).ready(function () {
                $.plot($("#placeholder2"), dataset2, options);
                $("#placeholder2").UseTooltip();
            });

            function gd(year, month, day) {
                return new Date(year, month, day).getTime();
            }
 
            var previousPoint = null, previousLabel = null;

            $.fn.UseTooltip = function () {
                $(this).bind("plothover", function (event, pos, item) {
                    if (item) {
                        if ((previousLabel != item.series.label) || (previousPoint != item.dataIndex)) {
                            previousPoint = item.dataIndex;
                            previousLabel = item.series.label;
                            $("#tooltip").remove();

                            var x = item.datapoint[0];
                            var y = item.datapoint[1];

                            var color = item.series.color;
            

                            showTooltip(item.pageX,
                            item.pageY,
                            color,
                            "<strong>" + item.series.label + "</strong><br>" + item.series.xaxis.ticks[x].label + " : <strong>" + y);
                        }
                    } else {
                        $("#tooltip").remove();
                        previousPoint = null;
                    }
                });
            };

            function showTooltip(x, y, color, contents) {
                $('<div id="tooltip">' + contents + '</div>').css({
                    position: 'absolute',
                    display: 'none',
                    top: y - 40,
                    left: x - 120,
                    border: '2px solid ' + color,
                    padding: '3px',
                    'font-size': '9px',
                    'border-radius': '5px',
                    'background-color': '#fff',
                    'font-family': 'Verdana, Arial, Helvetica, Tahoma, sans-serif',
                    opacity: 0.9
                }).appendTo("body").fadeIn(200);
            }
        }
        function flot_graph_long (array)
        {
            console.log(array);
            var maxarray = [];
            var data = [];
            var ticks = [];
            var inilength = 6;
            if (inilength > array.length)
                inilength = array.length;
            for (var i = 0; i < inilength; i++)
            {
                var max = 0;
                var name = "";
                for (var j = 0; j < array.length; j++)
                {
                    if (array[j][1] > max)
                    {
                        max = array[j][1];
                        name = array[j][0];
                        array[j][1] = parseInt(0);
                    }
                }
                maxarray.push([name, parseInt(max)]);
                data.push([parseInt(i), maxarray[i][1]]);
                ticks.push([parseInt(i), maxarray[i][0]]);

            }
            var outputlist = maxarray[1][0];
            for (var x = 2; x < maxarray.length-1; x++)
            {
                outputlist += ", " + maxarray[x][0];
            }
            document.getElementById("tts-text").innerHTML += "Your most listened to genre in the short term is: " + maxarray[0][0] + ", followed by " + outputlist + ", and " + maxarray[maxarray.length-1][0] + " \n ";
            var dataset = [
                {
                    label: "Total Count", data: data, color: "#5482FF"
                }
            ];
            var options = {
                series: {
                    bars: {
                        show: true,
                        align: "center",
                        barWidth: 0.5
                    }
                },
                xaxis: {
                    axisLabel: "Genres",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 10,
                    ticks: ticks
                },
                yaxis: {
                    axisLabel: "Total Count",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 3,
                },
                grid: {
                    hoverable: true,
                    borderWidth: 2,
                    backgroundColor: {colors: ["#ffffff", "#EDF5FF"]}
                }
            };

            $(document).ready(function () {
                $.plot($("#placeholder"), dataset, options);
                $("#placeholder").UseTooltip();
            });

            function gd(year, month, day) {
                return new Date(year, month, day).getTime();
            }
 
            var previousPoint = null, previousLabel = null;

            $.fn.UseTooltip = function () {
                $(this).bind("plothover", function (event, pos, item) {
                    if (item) {
                        if ((previousLabel != item.series.label) || (previousPoint != item.dataIndex)) {
                            previousPoint = item.dataIndex;
                            previousLabel = item.series.label;
                            $("#tooltip").remove();

                            var x = item.datapoint[0];
                            var y = item.datapoint[1];

                            var color = item.series.color;

                            //console.log(item.series.xaxis.ticks[x].label);                

                            showTooltip(item.pageX,
                            item.pageY,
                            color,
                            "<strong>" + item.series.label + "</strong><br>" + item.series.xaxis.ticks[x].label + " : <strong>" + y);
                        }
                    } else {
                        $("#tooltip").remove();
                        previousPoint = null;
                    }
                });
            };

            function showTooltip(x, y, color, contents) {
                $('<div id="tooltip">' + contents + '</div>').css({
                    position: 'absolute',
                    display: 'none',
                    top: y - 40,
                    left: x - 120,
                    border: '2px solid ' + color,
                    padding: '3px',
                    'font-size': '9px',
                    'border-radius': '5px',
                    'background-color': '#fff',
                    'font-family': 'Verdana, Arial, Helvetica, Tahoma, sans-serif',
                    opacity: 0.9
                }).appendTo("body").fadeIn(200);
            }
        }

        var userProfileSource = document.getElementById('user-profile-template').innerHTML,
            userProfileTemplate = Handlebars.compile(userProfileSource),
            userProfilePlaceholder = document.getElementById('user-profile');

            oauthSource = document.getElementById('oauth-template').innerHTML,
            oauthTemplate = Handlebars.compile(oauthSource),
            oauthPlaceholder = document.getElementById('oauth');

        var params = getHashParams();
		
		

        var access_token = params.access_token,
            state = params.state,
            storedState = localStorage.getItem(stateKey);
			
			

        if (access_token && (state == null || state !== storedState)) {
          alert('There was an error during the authentication');
        } else {
          localStorage.removeItem(stateKey);
          if (access_token) {
			$.ajax({
                url: 'https://api.spotify.com/v1/me',
                headers: {
                  'Authorization': 'Bearer ' + access_token
                },
                success: function(response) {
                  userProfilePlaceholder.innerHTML = userProfileTemplate(response);

                  $('#login').hide();
                  //document.getElementById("tts-text").innerHTML = "Please login in order to allow our app to make recommendations."
                  $('#loggedin').show();
                }
            });
            var longResponse;
            var shortResponse;
			$.ajax({
                url: 'https://api.spotify.com/v1/me/top/tracks',
                headers: {
                  'Authorization': 'Bearer ' + access_token
                },
				data: {"limit": "50", "time_range": "long_term"},
                offset: 0,
                time_range: 'long_term',
				json: true,
                success: function(response) {
				  longResponse = response;
                  $('#login').hide();
                  $('#loggedin').show();
				  if (response.items.length > 0){
                    //console.log("longResponse");
                    //console.log(longResponse);
                    var tracks = 50;
                    if (response.items.length < 50)
                    {
                        tracks = response.items.length;
                    }
                    //console.log("tracks");
                    //console.log(tracks);
                    var i;
                    var counter = 0;
                    var attempts = Math.floor(tracks / 5);
                    var finalamount = tracks % 5;
                    var total = response.items[0];
                    var amount = response.items[0].artists[0].id;
                    var array = [];
                    //console.log(array);
                    for (i = 0; i < tracks; i++)
                    {
                        var artistList = response.items[i].artists[0].id;
                        $.ajax({
                            url: 'https://api.spotify.com/v1/artists/' + artistList,
                            headers: {
                                'Authorization': 'Bearer ' + access_token
                            },
                            json: true,
                            success: function(artResponse) {
                                var genres = artResponse.genres;
                                for (var j = 0; j < genres.length; j++)
                                {
                                    var nExist = false;
                                    for (var k = 0; k < array.length; k++)
                                    {
                                        if (genres[j] == array[k][0])
                                        {
                                            array[k][1] += 1;
                                            nExist = true;
                                        }
                                    }
                                    if (nExist == false)
                                    {
                                        array.push([genres[j], parseInt(1)]);
                                    }
                                }
                            },
                            async: false
                        });
                    }
                    flot_graph_long(array);
				  }
				  
                }
            });
            
            $.ajax({
                url: 'https://api.spotify.com/v1/me/top/tracks',
                headers: {
                  'Authorization': 'Bearer ' + access_token
                },
				data: {"limit": "50", "time_range": "short_term"},
                offset: 0,
                time_range: 'short_term',
				json: true,
                success: function(response) {
				  shortResponse = response;
                  $('#login').hide();
                  $('#loggedin').show();
				  if (response.items.length > 0){
                    //console.log("shortResponse");
                    //console.log(shortResponse);
                    var tracks = 50;
                    if (response.items.length < 50)
                    {
                        tracks = response.items.length;
                    }
                    var i;
                    var array = [];
                    for (i = 0; i < tracks; i++)
                    {
                        var artistList = response.items[i].artists[0].id;
                        $.ajax({
                            url: 'https://api.spotify.com/v1/artists/' + artistList,
                            headers: {
                                'Authorization': 'Bearer ' + access_token
                            },
                            json: true,
                            success: function(artResponse) {
                                var genres = artResponse.genres;
                                for (var j = 0; j < genres.length; j++)
                                {
                                    var nExist = false;
                                    for (var k = 0; k < array.length; k++)
                                    {
                                        if (genres[j] == array[k][0])
                                        {
                                            array[k][1] += 1;
                                            nExist = true;
                                        }
                                    }
                                    if (nExist == false)
                                    {
                                        array.push([genres[j], parseInt(1)]);
                                    }
                                }
                            },
                            async: false
                        });
                    }
                    flot_graph_short(array);
				  }
				  
                }
            });

          } else {
              $('#login').show();
              $('#loggedin').hide();
          }

          document.getElementById('login-button').addEventListener('click', function() {

            var client_id = '50827088dd9a450cab32c88509bf85f3'; // Your client id
            //var redirect_uri = 'http://project3/bands/'; // Your redirect uri
			var redirect_uri = 'http://people.tamu.edu/~jcarpman100/Project_3/visual/'; // Your redirect uri

            var state = generateRandomString(16);

            localStorage.setItem(stateKey, state);
            var scope = 'user-read-private user-read-email user-top-read';

            var url = 'https://accounts.spotify.com/authorize';
            url += '?response_type=token';
            url += '&client_id=' + encodeURIComponent(client_id);
            url += '&scope=' + encodeURIComponent(scope);
            url += '&redirect_uri=' + encodeURIComponent(redirect_uri);
            url += '&state=' + encodeURIComponent(state);

            window.location = url;
          }, false);
        }
      })();
    </script>
    
    <script src="../text2speech-test.js"></script>
    <script language="javascript" type="text/javascript" src="jquery-3.5.1.min.js"></script>
	<script language="javascript" type="text/javascript" src="jquery.flot.js"></script>
	<script language="javascript" type="text/javascript" src="jquery.flot.symbol.js"></script>
	<script language="javascript" type="text/javascript" src="jquery.flot.axislabels.js"></script>
	<script language="javascript" type="text/javascript" src="jquery.flot.time.js"></script>
	<body>
		<header>
			
			</header><!-- .page-header -->
			<hr>
				
				<h2>Long Term (Full History)</h2>
				<div id="placeholder" style="width:1000px;height:300px;margin: 0 auto"></div>
				<script type="text/javascript"></script>
				
				<br style="clear:left;"/>
                <hr>
                <h2>Short Term (Last 4 Weeks)</h2>
                <div id="placeholder2" style="width:1000px;height:300px;margin: 0 auto"></div>
				<script type="text/javascript"></script>

<hr>
</center>
	<?php
		
		
		
		/*if (isset($_COOKIE["poorSight"])){
			$poorSight = $_COOKIE["poorSight"];
			$colorBlind = $_COOKIE["colorBlind"];
			} else */if (!isset($poorSight)){
			$poorSight = "no";
			$colorBlind = "normal";
		}
		
		
		global $poorSight;
		global $colorBlind;
		
		/*if (isset($_POST["submit"])): 
			
			if ($_SERVER["REQUEST_METHOD"] == "POST") {
			if (isset($_POST["poorSight"])){
			$poorSight = $_POST["poorSight"];
			
			}
			if (isset($_POST["colorBlind"])){
			$colorBlind = $_POST["colorBlind"];
			
			}
			setcookie("poorSight", $poorSight, time()+3600);
			setcookie("colorBlind", $colorBlind, time()+3600);
			}
			
			endif;
			
			if(!session_id()){ 
			session_start();
			}
			$_SESSION['poorSight'] = $poorSight;
			$_SESSION['colorBlind'] = $colorBlind;
		*/
		
	?>
	<!--
	<form action = # method = "POST">
		<label for="poorSight">Would you like your results converted to text?: </label>
		<input type = "radio" name = "poorSight" value = "yes">Yes
		<input type = "radio" name = "poorSight" value = "no">No <br>
		
		<label for="colorBlind">How would you like your colors? : </label>
		<select id="colorBlind" name="colorBlind">
		<option value="normal">Normal</option>
		<option value="protanopia">Protanopia</option>
		<option value="deuteranopia">Deuteranopia</option>
		<option value="tritanopia">Tritanopia</option>
		</select> 
		<br>
		<input type="submit" name="submit" value="Submit"/>
		</form>-->
		<?php if($poorSight == "yes"){
		echo "<center><target=\"_blank\"> <button id = \"tts-button\" class = \"button\" style = \"width:100%\">Convert this page to audio</button></a></center>";
		}
		?> <br>
		Current TTS: <?php echo $poorSight; ?> <br>
	Current Color Sight: <?php echo $colorBlind; ?> 
</center>

</html>
