/**
 * This is an example of a basic node.js script that performs
 * the Authorization Code oAuth2 flow to authenticate against
 * the Spotify Accounts.
 *
 * For more information, read
 * https://developer.spotify.com/web-api/authorization-guide/#authorization_code_flow
 */

var express = require('express'); // Express web server framework
var request = require('request'); // "Request" library
var cors = require('cors');
var querystring = require('querystring');
var cookieParser = require('cookie-parser');

var client_id = '50827088dd9a450cab32c88509bf85f3'; // Your client id
var client_secret = '77a5f1b1c31141b3bab6d891d7882100'; // Your secret
var redirect_uri = 'http://localhost:8888/callback/'; // Your redirect uri

const fs = require('fs')

// Data which will write in a file.
//let data = "Learning how to write in a file."



/**
 * Generates a random string containing numbers and letters
 * @param  {number} length The length of the string
 * @return {string} The generated string
 */
var generateRandomString = function(length) {
  var text = '';
  var possible = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';

  for (var i = 0; i < length; i++) {
    text += possible.charAt(Math.floor(Math.random() * possible.length));
  }
  console.log(text)
  return text;
};

var stateKey = 'spotify_auth_state';

var app = express();

app.use(express.static(__dirname + '/public'))
   .use(cors())
   .use(cookieParser());

app.get('/login', function(req, res) { // first call that requests authorization to access data

  var state = generateRandomString(16);
  res.cookie(stateKey, state);

  // your application requests authorization
  var scope = 'user-read-private user-read-email user-top-read';
  res.redirect('https://accounts.spotify.com/authorize?' +
    querystring.stringify({
      response_type: 'code',
      client_id: client_id,
      scope: scope,
      redirect_uri: redirect_uri,
      state: state
    }));
});

app.get('/callback', function(req, res) {

  // your application requests refresh and access tokens
  // after checking the state parameter

  var code = req.query.code || null;
  var state = req.query.state || null;
  var storedState = req.cookies ? req.cookies[stateKey] : null;

  if (state === null || state !== storedState) {
    res.redirect('/#' +
      querystring.stringify({
        error: 'state_mismatch'
      }));
  } else {
    res.clearCookie(stateKey);
    var authOptions = {
      url: 'https://accounts.spotify.com/api/token',
      form: {
        code: code,
        redirect_uri: redirect_uri,
        grant_type: 'authorization_code'
      },
      headers: {
        'Authorization': 'Basic ' + (new Buffer(client_id + ':' + client_secret).toString('base64'))
      },
      json: true
    };

    request.post(authOptions, function(error, response, body) {
      if (!error && response.statusCode === 200) {

        var access_token = body.access_token,
            refresh_token = body.refresh_token;

        var options = {
          url: 'https://api.spotify.com/v1/me',
          headers: { 'Authorization': 'Bearer ' + access_token },
          json: true
        };

        //console.log(access_token)

        // use the access token to access the Spotify Web API
        request.get(options, function(error, response, body) {
          //console.log("PRINTING PERSONAL INFO \n")
          //console.log(body);

        });



        var options ={
          url: "https://api.spotify.com/v1/me/top/artists?time_range=short_term&limit=1&offset=0",
          headers: { 'Authorization': 'Bearer ' + access_token },
          // limit: 1,
          // offset: 0,
          // time_range:'short_term',
          //country: 'ES'
          json: true
        };

        request.get(options, function(error, response, body) {
          console.log("PRINTING SHORT TERM INFO \n")
          console.log("\n")
          console.log(body);
          //console.log("PRINTING ERROR INFO \n")
          //console.log(error);
          console.log("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH \n")
          console.log("\n")
        //  console.log(response);
        });


        var options ={
          url: "https://api.spotify.com/v1/me/top/artists?time_range=long_term&limit=1&offset=0",
          headers: { 'Authorization': 'Bearer ' + access_token },
          limghdhit: 1,
          offset: 0,
          time_range:'long_term',

          //country: 'ES'
          json: true
        };

        request.get(options, function(error, response, body) {
          console.log("PRINTING LONG TERM INFO \n")
          console.log("\n")
          console.log(body);
          // Write data in 'Output.txt' .
          //fs.writeFile('Output.json', body, (err) => {

          // In case of a error throw err.
          //if (err) throw err;
		//})
          //console.log("PRINTING ERROR INFO \n")
          //console.log(error);
          console.log("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH \n")
          console.log("\n")
        //  console.log(response);
        });

        // we can also pass the token to the browser to make requests from there
        res.redirect('/#' +
          querystring.stringify({
            access_token: access_token,
            refresh_token: refresh_token
          }));
      } else {
        res.redirect('/#' +
          querystring.stringify({
            error: 'invalid_token'
          }));
      }
    });
  }
});

app.get('/refresh_token', function(req, res) {

  // requesting access token from refresh token
  var refresh_token = req.query.refresh_token;
  var authOptions = {
    url: 'https://accounts.spotify.com/api/token',
    headers: { 'Authorization': 'Basic ' + (new Buffer(client_id + ':' + client_secret).toString('base64')) },
    form: {
      grant_type: 'refresh_token',
      refresh_token: refresh_token
    },
    json: true
  };

  request.post(authOptions, function(error, response, body) {
    if (!error && response.statusCode === 200) {
      var access_token = body.access_token;
      res.send({
        'access_token': access_token
      });
    }
  });
});

console.log('Listening on 8888');
app.listen(8888);
