<?php
class mq3{
 public $link='';
 function __construct($value){
  $this->connect();
  $this->storeInDB($value);
 }

 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'alcohol') or die('Cannot select the DB');
 }

 function storeInDB($value){
  $query = "insert into readings set value='".$value."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }

}
if($_GET['value'] != ''){
 $mq3=new mq3($_GET['value']);
}

?>
