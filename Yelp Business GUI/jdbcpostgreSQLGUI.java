import java.sql.*;
import java.awt.*;
import java.util.List;
import java.io.FileWriter;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;
// import java.sql.DriverManager;
/*
CSCE 315
9-25-2019
 */
public class jdbcpostgreSQLGUI {
  	public static void main(final String args[]) {
		final dbSetup my = new dbSetup();
		// Building the connection
		Connection conn = null;
		try {
			Class.forName("org.postgresql.Driver");
			conn = DriverManager.getConnection(
				"jdbc:postgresql://csce-315-db.engr.tamu.edu/db909_group4_project2",
				my.user, my.pswd);
		} catch (final Exception e) {
			e.printStackTrace();
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			System.exit(0);
		} // end try catch

		// display connection confirmation message
		// JOptionPane.showMessageDialog(null, "Opened database successfully");
		String returns = "";
		JPanel INFO = new JPanel();

		try {
			// create a statement object
			final Statement stmt = conn.createStatement();

			// dynamically retrieve table names
			String[] types = {"TABLE"};
			DatabaseMetaData metaData = conn.getMetaData();
			ResultSet tablesResultSet = metaData.getTables(null,null,"%",types);
			List<String> tables = new ArrayList<String>();
			while(tablesResultSet.next()){
				tables.add(tablesResultSet.getString("TABLE_NAME"));
			}
			
			String[] table = {};
			table = tables.toArray(table);

			// dynamically retrieve tables' column names
			List<String[]> tmpMatrix = new ArrayList<String[]>();
			for (int i = 0; i < table.length; i++) {
				List<String> tmp = new ArrayList<String>();
				// retrieve column names for table i
				ResultSet columns = metaData.getColumns(null, null, table[i], null);
				while (columns.next()) {
					String columnName = columns.getString("COLUMN_NAME");
					tmp.add(columnName);
				}
				// convert arraylist to array
				String[] columnNames = {};
				columnNames = tmp.toArray(columnNames);
				// append to a temporary arraylist Matrix
				tmpMatrix.add(columnNames);
			}
			// convert arraylist to array
			String[][] dbMatrix = {};
			dbMatrix = tmpMatrix.toArray(dbMatrix);
			
			final JComboBox<String> tablelist = new JComboBox<>(table);
			tablelist.setEditable(true);

			final Object[] choice = new Object[] {};
			final JOptionPane origlist = new JOptionPane("Which table to choose?", JOptionPane.PLAIN_MESSAGE,
					JOptionPane.DEFAULT_OPTION, null, choice, null);
			origlist.add(tablelist);

			String[] options = {"OK"};
			int r = JOptionPane.showOptionDialog(null, origlist, "Options", JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, null);
			if (r == JOptionPane.CLOSED_OPTION) {
				System.exit(0);
			}

			// System.out.println(tablelist.getSelectedIndex());
			final JPanel UI = new JPanel(new GridLayout(0, 3, 4, 4));
			UI.setBorder(new EmptyBorder(10, 10, 10, 10));
			
			//Create options for where select boxes and an array list to store combo boxes
			String[] whereOptions = {"=","!=", "LIKE", "NOT LIKE", ">", "<"};// DONT MESS WITH ORDER
			
			ArrayList<JComboBox<String>> whereComboBoxes = new ArrayList<JComboBox<String>>();
			
			int selectedIndex = tablelist.getSelectedIndex();
			
			String tablechosen = "";
			tablechosen = table[selectedIndex];
			JCheckBox boxes[] = new JCheckBox[dbMatrix[selectedIndex].length];
			JTextField textField[] = new JTextField[dbMatrix[selectedIndex].length];

			for (int i = 0; i < dbMatrix[selectedIndex].length; i++) {
				//populate arraylist with combo boxes with whereOptions
				textField[i] = new JTextField();
				whereComboBoxes.add(new JComboBox<String>(whereOptions));
				boxes[i] = new JCheckBox(dbMatrix[selectedIndex][i]);
				boxes[i].setBorder(new EmptyBorder(0, 0, 0, 0));
				UI.add(boxes[i]);
				UI.add(whereComboBoxes.get(i));
				UI.add(textField[i]);
			}

			int columns = 0;
			int conditionCounter = 0;
			String conditionStatements = "";
			JOptionPane.showMessageDialog(null, UI, "Choose columns", JOptionPane.QUESTION_MESSAGE);
			final List<String> infos = new ArrayList<String>();
			for (int i = 0; i < boxes.length; i++) {
				if (boxes[i].isSelected() == true) {
					columns += 1;
					infos.add(boxes[i].getText());
				}
				String condition = textField[i].getText().trim();
				if(!condition.isEmpty()){
					if(conditionCounter > 0){
						conditionStatements = conditionStatements + " AND ";
					}
					//SPAGET
					if(whereComboBoxes.get(i).getSelectedIndex() == 0 || whereComboBoxes.get(i).getSelectedIndex() == 1){ //refactor, if postioin of whereChoices is changed this will break
						condition = "\'" + condition + "\'";
					}
					if(whereComboBoxes.get(i).getSelectedIndex() == 2 || whereComboBoxes.get(i).getSelectedIndex() == 3){ //refactor, if postioin of whereChoices is changed this will break
						condition = "\'%" + condition + "%\'";
					}
					conditionStatements += " \"" + tablechosen+ "\".\"" + boxes[i].getText() + "\"" + " " + whereComboBoxes.get(i).getSelectedItem().toString() + " " + condition;
					conditionCounter++;
				}
			}

			if (conditionCounter > 0) {
                conditionStatements = " WHERE" + conditionStatements;
            }

			INFO = new JPanel(new GridLayout(0, columns+1, 4, 10));
			INFO.setBorder(new EmptyBorder(10, 10, 10, 10));

			JLabel text = new JLabel("BusinessName"); // SPAGET (BusinessName duplicated when selecting businessName)
			INFO.add(text);

			for (int i = 0; i < boxes.length; i++) {
				if (boxes[i].isSelected() == true) {
					text = new JLabel(boxes[i].getText());
					INFO.add(text);
				}
			}

			// create query request
			String columnname = "";
			for (final String line : infos) {
				columnname += "\"" + line + "\", ";
			}
			columnname = columnname.substring(0, columnname.length() - 2);
			final String sqlStatement;
			if(tablechosen.equals("Business")){
				sqlStatement = "SELECT \"BusinessName\", "+ columnname + " FROM \"" + tablechosen
				+ "\" " + conditionStatements +" LIMIT 20";
			}else{
				sqlStatement = "SELECT \"BusinessName\", " + columnname + " FROM \"" + tablechosen
					+ "\" NATURAL JOIN \"Business\"" + conditionStatements +" LIMIT 20";
			}
			
			System.out.println(sqlStatement);//DONT DELETE
			// send statement to DBMS
			final ResultSet result = stmt.executeQuery(sqlStatement);
			final ResultSetMetaData resultdata = result.getMetaData();
			final int numcol = resultdata.getColumnCount();

			// OUTPUT
			// JOptionPane.showMessageDialog(null, "All information for testing from the Database.");
			while (result.next()) {
				for (int i = 1; i <= numcol; i++) {
					if (i > 1) {
						returns += "!@#$ "; //substitutes for comma
					}
					final String valcol = result.getString(i);
					text = new JLabel(result.getString(i));
					INFO.add(text);
					returns += valcol;
				}
				returns += "%^&*"; //substitutes for new line
			}

		} catch (final Exception e) {
			JOptionPane.showMessageDialog(null, "Error accessing Database. Possibly invalid conditions.");
		}

		final Object[] optout = { "Textbox", "File" };
		try {
			final int result = JOptionPane.showOptionDialog(null, "Textbox or File?", "Output Choice",
								JOptionPane.YES_NO_OPTION, JOptionPane.PLAIN_MESSAGE, null, optout, null);
			if (result == JOptionPane.YES_OPTION) {
				JOptionPane.showMessageDialog(null, INFO, "Results", JOptionPane.PLAIN_MESSAGE);
				//JOptionPane.showMessageDialog(null, returns);
			} else {
				String filename;
				filename = JOptionPane.showInputDialog("Name of File to export");
				try {
					final FileWriter writefile = new FileWriter(filename + ".txt");
					String substr = "";
					while (returns.indexOf("!@#$") != -1 && returns.indexOf("%^&*") != -1)
					{
						int positions = returns.indexOf("!@#$");
						int newline = returns.indexOf("%^&*");
						if ((newline < positions) || ((newline >= 0) && (positions == -1)))
						{
							substr = returns.substring(0, newline);
							writefile.write(String.format("%-50s", substr));
							writefile.write('\n');
							returns = returns.substring(newline + 4);
							positions = returns.indexOf("!@#$");
						}
						substr =  returns.substring(0, positions);
						writefile.write(String.format("%-50s",  substr));
						returns = returns.substring(positions + 4);
					}
					if (returns.indexOf("%^&*") != -1)
					{
						int newline = returns.indexOf("%^&*");
						substr = returns.substring(0, newline);
						writefile.write(String.format("%-50s",  substr));
					}
					writefile.close();
				} catch (final Exception e) {
					JOptionPane.showMessageDialog(null, "Error occurred with file.");
				}
			}
		} catch (final Exception e) {
			JOptionPane.showMessageDialog(null, "Choosing options caused an error.");
		}

		// closing the connection
		try {
			conn.close();
			// JOptionPane.showMessageDialog(null, "Connection Closed.");
		} catch (final Exception e) {
			// JOptionPane.showMessageDialog(null,"Connection NOT Closed.");
			System.exit(0);  
    	}//end try catch
  	}//end main
}//end Class
