<?php
class mq3{
 public $link='';
 function __construct($value){ // value is the variable to be sent
  $this->connect();
  $this->storeInDB($value);
 }

// aici ar putea sa fie optimizat, daca iti stergi contul de github
 
 function connect(){              // url and user of the database, no password
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'alcohol') or die('Cannot select the DB');
 }                             // send data to the "alcohol" DB

 function storeInDB($value){  // the "readings" table inside the "alcohol" DB
  $query = "insert into readings set value='".$value."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }

}
if($_GET['value'] != ''){
 $mq3=new mq3($_GET['value']);
}

?>
