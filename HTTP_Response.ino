void HTTP_Response(WiFiEspClient client) {
  // if you've gotten to the end of the line (received a newline
  // character) and the line is blank, the http request has ended,
  // so you can send a reply
  Serial.println(F("Sending response"));

  // send a standard http response header
  // use \r\n instead of many println statements to speedup data send
  client.print(F("HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "Connection: close\r\n"  // the connection will be closed after completion of the response
                 "Refresh: 20\r\n"        // refresh the page automatically every 20 sec
                 "\r\n"));

  client.print(F(R"=====(
<!DOCTYPE html>
<html>
<head>
<style>
.dropbtn {
  background-color: Maroon;
  color: white;
  padding: 16px;
  font-size: 16px;
  border: none;
  cursor: pointer;
  text-align: left;
}

.dropdown {
  position: relative;
  display: inline-block;
}

.dropdown-content {
  display: none;
  position: absolute;
  background-color: maroon;
  min-width: 160px;
  z-index: 1;
}

.dropdown-content a {
  color: black;
  padding: 12px 16px;
  text-decoration: none;
  display: block;
}

.dropdown-content a:hover {background-color: #f1f1f1}

.dropdown:hover .dropdown-content {
  display: block;
}

.dropdown:hover .dropbtn {
  background-color: #660000;
}

table {
  border-collapse: collapse;
  width: 100%;
}

th {
  background-color: Maroon;
  color: white;
  height: 50px;
  text-align: left;
  border-bottom: 5px solid #ddd;
}

td {
  padding: 8px;
  text-align: left;
  border: 1px solid #ddd;
}
tr:hover {background-color:#f5f5f5;}
</style>
</head>
<body>
<table> 
  <tr>
    <th><div class="dropdown">
      <button class="dropbtn">Menu</button>
      <div class="dropdown-content">
      <a href="C:\Users\G00362643\OneDrive - GMIT\84180484_217367179395303_8691209302364389376_n.jpg">Block Diagram</a>
      </div>
    </div></th>
    <th></th>
    <th></th>
    <th></th>
    <th></th>
  </tr>  
  <tr>
    <td>Coffee:</td>
    <td>Americano</td>
    <td>Latte</td>
    <td>Cappuccino</td>
    <td>Mocha</td>
  </tr>
  <tr>
    <td>Ingredients:</td>
    <td>Espresso</td>
    <td>Espresso, Steamed Milk</td>
    <td>Double Espresso, Steamed Milk Foam, Hot Milk</td>
    <td>Espresso, Hot Milk, Chocolate</td>
  </tr>
  <tr>
    <td>Prepare:</td>
    <td><input type=button value="Click Me" onmousedown=location.href="/1" onmouseup=location.href="/f"></td>
    <td><input type=button value="Click Me" onmousedown=location.href="/2"></td>
    <td><input type=button value="Click Me" onmousedown=location.href="/3"></td>
    <td><input type=button value="Click Me" onmousedown=location.href="/4"></td>
  </tr>
</table>
</body>
</html>
  )====="));
}
