package com.example.sudokuchecker;

import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.app.AlertDialog;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;

public class MainActivity extends ActionBarActivity {
	
	Button solve;
	EditText firstRow, secondRow, thirdRow, fourthRow, fifthRow, sixthRow, seventhRow, eighthRow, ninthRow; 
	TextView answer;
	
	private AlertDialog.Builder emptyAlert;
	private AlertDialog.Builder alert;
	private AlertDialog.Builder errorAlert;
    private Button btAbout;
	
    
    static {
		System.loadLibrary("SudokuChecker");
	}
    
	//Native functions
	public native int mainSolve(String x);
	
	int result = 0;
	
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        //Get all edittexts!
        firstRow = (EditText)findViewById(R.id.editText1);
        secondRow = (EditText)findViewById(R.id.editText2);
        thirdRow = (EditText)findViewById(R.id.editText3);
        fourthRow = (EditText)findViewById(R.id.editText4);
        fifthRow = (EditText)findViewById(R.id.editText5);
        sixthRow = (EditText)findViewById(R.id.editText6);
        seventhRow = (EditText)findViewById(R.id.editText7);
        eighthRow = (EditText)findViewById(R.id.editText8);
        ninthRow = (EditText)findViewById(R.id.editText9);
        
        setContentView(R.layout.activity_main);
        
        //Declare Button and handle it
        solve = (Button)findViewById(R.id.solve_button);
        //Setup OnClickHandler for Solve Button
    	solve.setOnClickListener(new View.OnClickListener() {
//    		
    		public void onClick(View v) {
			String userInput = firstRow.getText().toString();
			userInput = userInput + secondRow.getText().toString();
			userInput = userInput + thirdRow.getText().toString();
			userInput = userInput + fourthRow.getText().toString();
			userInput = userInput + fifthRow.getText().toString();
			userInput = userInput + sixthRow.getText().toString();
			userInput = userInput + seventhRow.getText().toString();
			userInput = userInput + eighthRow.getText().toString();
			userInput = userInput + ninthRow.getText().toString();
			if((secondRow.getText().toString() + secondRow.getText().toString() + secondRow.getText().toString() + 
					secondRow.getText().toString() + secondRow.getText().toString() + secondRow.getText().toString() + 
					secondRow.getText().toString() + secondRow.getText().toString() + secondRow.getText().toString()).length() != 81){
				emptyAlert = new AlertDialog.Builder(MainActivity.this);
				emptyAlert.setTitle("ERROR");
		        emptyAlert.setMessage("Please enter all values!");
		        emptyAlert.show();
			}
			//Call native c Function mainSolve with the passed in string of characters
			result = mainSolve(userInput);
			if(result==1){
				alert = new AlertDialog.Builder(MainActivity.this);
				alert.setTitle("Correct!");
		        alert.setMessage("You've successfully solved your sudoku Board");
		        alert.show();
			}
			else{
				errorAlert = new AlertDialog.Builder(MainActivity.this);
				errorAlert.setTitle("Incorrect");
		        errorAlert.setMessage("Invalid Board");
		        errorAlert.show();
			}
		}
	});
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
   
}




