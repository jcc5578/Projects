import java.sql.*;
import java.awt.*;
import java.util.List;
import java.util.jar.Attributes.Name;
import java.io.FileWriter;
import java.io.IOException;
import java.io.File;
import java.util.*;
import java.lang.Math;

import javax.swing.*;
import javax.swing.border.*;

import java.awt.GridBagConstraints;  
import java.awt.GridBagLayout; 
import java.awt.event.*;
// import java.sql.DriverManager;

public class jdbcpostgreSQLGUI2 {

	public static ArrayList<queryData> data = new ArrayList<queryData>();

	static String getQuery() {

		System.out.println("SIZE " + data.size() );
		String columns = "";
		String tables[] = new String[data.size()];
		String conditionStatement = "";
		int conditionCounter = 0;
		String query = new String();

		for(int x = 0; x < data.size(); x++){
			
			ArrayList<JComboBox<String>> whereComboBoxes = data.get(x).whereComboBoxes;
			JCheckBox boxes[] = data.get(x).boxes;
   			JTextField textField[] = data.get(x).textField;
    		String tableSelected = data.get(x).tableSelected;
					
			List<String> infos = new ArrayList<String>();
			for (int i = 0; i < boxes.length; i++) {
				if (boxes[i].isSelected() == true) {
					infos.add(boxes[i].getText());
				}
				String condition = textField[i].getText().trim();
				if(!condition.isEmpty()){
					if(conditionCounter > 0){
						conditionStatement = conditionStatement + " AND ";
					}
					//SPAGET
					if(whereComboBoxes.get(i).getSelectedIndex() == 0 || whereComboBoxes.get(i).getSelectedIndex() == 1){ //refactor, if postioin of whereChoices is changed this will break
						condition = "\'" + condition + "\'";
					}
					if(whereComboBoxes.get(i).getSelectedIndex() == 2 || whereComboBoxes.get(i).getSelectedIndex() == 3){ //refactor, if postioin of whereChoices is changed this will break
						condition = "\'%" + condition + "%\'";
					}
					conditionStatement += " \"" + tableSelected + "\".\"" + boxes[i].getText() + "\"" + " " + whereComboBoxes.get(i).getSelectedItem().toString() + " " + condition;
					conditionCounter++;
				}
			}

			// create query request
			for (String line : infos) {
				System.out.println(line);
				columns += "\"" + line + "\", ";
			}

			tables[x] = tableSelected;
					
		}
		//////////////// END OF GENERATING THE QUERY ////////////////
		if(conditionStatement != ""){
			//@@@@START HERE@@@@@@
			conditionStatement = " WHERE" + conditionStatement;
		}
		columns = columns.substring(0, columns.length() - 2);

		query = "SELECT " + columns + " FROM";

		for(int i = 0; i < tables.length; i++){
			if(i == 0){
				query = query + " \"" + tables[i]+ "\"";
			}
			else{
				query = query + " NATURAL JOIN \"" + tables[i] + "\" " ;
			}
		}

		query = query + conditionStatement + " LIMIT 50";

		System.out.println(query);

		return query;
		
	}
	
	static String[] getColumnNames(Connection conn, String tableSelected) {
		// get the selected table's column names
		String[] columnNames = {};

		try {
			DatabaseMetaData metaData = conn.getMetaData();

			List<String> tmp = new ArrayList<String>();
			ResultSet columns = metaData.getColumns(null, null, tableSelected, null);
			while (columns.next()) {
				String columnName = columns.getString("COLUMN_NAME");
				tmp.add(columnName);
			}

			columnNames = tmp.toArray(columnNames);

		} catch (Exception e) {
			System.out.println(e);
		}
		return columnNames;
	}

	static String[] getTableNames(Connection conn) {
		// dynamically retrieve table names
		String[] table = {};
		try {
			String[] types = { "TABLE" };
			DatabaseMetaData metaData = conn.getMetaData();
			ResultSet tablesResultSet = metaData.getTables(null, null, "%", types);
			List<String> tables = new ArrayList<String>();
			while (tablesResultSet.next()) {
				tables.add(tablesResultSet.getString("TABLE_NAME"));
			}

			table = tables.toArray(table);
		} catch (Exception e) {
			System.out.println(e);
		}

		return table;
	}
	
	static int getDistance(ArrayList<String> franchiselist, int compareindex, ArrayList<Integer> visited)
	{
		double maxdist = 0;
		int indexpos = 0;
		for (int i = 2; i < franchiselist.size(); i+=4)
		{
			boolean indexvisited = false;
			double longitude1 = Double.parseDouble(franchiselist.get(i));
			double latitude1 = Double.parseDouble(franchiselist.get(i+1));
			double latitude2 = Double.parseDouble(franchiselist.get(compareindex+1));
			double longitude2 = Double.parseDouble(franchiselist.get(compareindex));
			double distance = Math.sqrt(Math.pow(longitude1-longitude2, 2) + Math.pow(latitude1-latitude2, 2));
			if (distance > maxdist)
			{
				for (int j = 0; j < visited.size(); j++)
				{
					if (i == visited.get(j))
					{
						indexvisited = true;
					}
				}
				//makes sure the same business won't appear again
				if (indexvisited == false) {
					maxdist = distance;
					indexpos = i;
				}
				if (visited.size() == 0)
				{
					maxdist = distance;
					indexpos = i;
				}
			}
		}
		return indexpos;
	}

	static void homeMenu(JFrame home, Connection conn) {
		JPanel menu = new JPanel(new GridLayout(6, 1, 20, 20));
		menu.setBorder(new EmptyBorder(20, 20, 20, 20));

		// Select Table Button
		ImageIcon searchIcon = new ImageIcon(
			new ImageIcon("assets/searchicon.png", "A Search Icon").getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH)
		);
		JButton simpleQuery = new JButton("Search", searchIcon);		
		simpleQuery.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				home.getContentPane().removeAll();	
				simpleQueryContainer(home, conn);
			}
		});

		JButton Question1 = new JButton("Find Shortest Chain");		
		Question1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				home.getContentPane().removeAll();	
				Question1(home, conn);
			}
		});

		ImageIcon commentIcon = new ImageIcon(
			new ImageIcon("assets/comment.png", "A Reviews Icon").getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH)
		);
		JButton Question2 = new JButton("See User Reviews", commentIcon);		
		Question2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				home.getContentPane().removeAll();	
				Question2(home, conn);
			}
		});

		ImageIcon franchiseIcon = new ImageIcon(
			new ImageIcon("assets/franchise.png", "A Franchise Icon").getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH)
		);
		JButton Question3 = new JButton("Find Top 5 Restaurant Franchises", franchiseIcon);		
		Question3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				home.getContentPane().removeAll();	
				Question3(home, conn);
			}
		});

		ImageIcon localIcon = new ImageIcon(
			new ImageIcon("assets/location.png", "A Local Icon").getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH)
		);
		JButton Question4 = new JButton("Find Best Local Restaurants Near Me", localIcon);		
		Question4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				home.getContentPane().removeAll();	
				Question4(home, conn);
			}
		});

		ImageIcon restIcon = new ImageIcon(
			new ImageIcon("assets/restaurant.png", "A Restaurants Icon").getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH)
		);
		JButton Question5 = new JButton("Find the Most Popular Restaurant Near Me", restIcon);		
		Question5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				home.getContentPane().removeAll();	
				Question5(home, conn);
			}
		});

		menu.add(simpleQuery);

		menu.add(Question1);
		menu.add(Question2);
		menu.add(Question3);
		menu.add(Question4);
		menu.add(Question5);
		
		home.add(menu);
		SwingUtilities.updateComponentTreeUI(home);
	}

	static void simpleQueryContainer(JFrame home, Connection conn) {
		// GridBagConstraints c = new GridBagConstraints();
		// c.fill = GridBagConstraints.HORIZONTAL;
		// c.ipady = 40;
		// c.weightx = 0.0;  
		// c.gridwidth = 3;  
		// c.gridx = 0;  
		// c.gridy = 0;

		JPanel simpleQuery = new JPanel(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();

		simpleQuery.setBorder(new EmptyBorder(10, 10, 10, 10));

		gbc.insets = new Insets(10, 10, 10, 10);
		
		ArrayList<JComboBox> comboBoxes = new ArrayList<JComboBox>();

		// Select Table Text
		JLabel tableSelectLabel = new JLabel("Select a table:");
		simpleQuery.add(tableSelectLabel);

		// Select Table JComboBox
		String[] table = getTableNames(conn);
		JComboBox<String> tableSelection = new JComboBox<>(table);
		tableSelection.setEditable(true);
		simpleQuery.add(tableSelection);

		comboBoxes.add(tableSelection);

		// Select Table Button
		JButton tableConfirmation = new JButton("OK");
		simpleQuery.add(tableConfirmation);

		tableConfirmation.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ArrayList<String> tableSelected = new ArrayList<String>();
				for(int i = 0; i < comboBoxes.size(); i++){
					tableSelected.add((String)comboBoxes.get(i).getItemAt(comboBoxes.get(i).getSelectedIndex()));
					//System.out.println( i + " " + tableSelected.get(i));
				}
				

				home.getContentPane().removeAll();	

				// call add simpleQueryContainer2 for column selection
				simpleQueryContainer2(home, conn, tableSelected, 0);
			}
		});
		// JOIN Button
		JButton joinButton = new JButton("JOIN");
		simpleQuery.add(joinButton);

		joinButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {	
				JComboBox<String> joinTable = new JComboBox<>(table);
				joinTable.setEditable(true);
				
				gbc.gridy++;
				simpleQuery.add(joinTable);
				
				comboBoxes.add(joinTable);
				


				SwingUtilities.updateComponentTreeUI(home);
				//System.out.println(comboBoxes.size());
			}
		});
		
		home.add(simpleQuery);
		SwingUtilities.updateComponentTreeUI(home);
	}

	static void simpleQueryContainer2(JFrame home, Connection conn, ArrayList<String> tableSelected, int iteration) {
		// Column Selection Container
		

			final String tableSelectedCurr = tableSelected.get(iteration);
			// get Column Names array
			String[] columnNames = getColumnNames(conn, tableSelectedCurr);
			// for (int i = 0; i < columnNames.length; i++) {
			// 	System.out.println(columnNames[i]);
			// }

			JPanel simpleQuery2 = new JPanel(new GridLayout(0, 3, 4, 4));

			//////////////// START OF MAJOR EDIT ////////////////

			String[] whereOptions = {"=","!=", "LIKE", "NOT LIKE", ">", "<"};// DONT MESS WITH ORDER

			ArrayList<JComboBox<String>> whereComboBoxes = new ArrayList<JComboBox<String>>();
			JCheckBox boxes[] = new JCheckBox[columnNames.length];
			JTextField textField[] = new JTextField[columnNames.length];

			for (int i = 0; i < columnNames.length; i++) {
				//populate arraylist with combo boxes with whereOptions
				textField[i] = new JTextField();
				whereComboBoxes.add(new JComboBox<String>(whereOptions));
				boxes[i] = new JCheckBox(columnNames[i]);
				boxes[i].setBorder(new EmptyBorder(0, 0, 0, 0));
				simpleQuery2.add(boxes[i]);
				simpleQuery2.add(whereComboBoxes.get(i));
				simpleQuery2.add(textField[i]);
			}

			//////////////// END OF MAJOR EDIT ////////////////		

			//////////////// START OF ACTION LISTENER ////////////////	

			JButton tableConfirmation = new JButton("NEXT");
			simpleQuery2.add(tableConfirmation);

			if(iteration == tableSelected.size()-1){
				//System.out.println("IF!!!!");
				tableConfirmation.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						
						home.getContentPane().removeAll();	
						data.add(new queryData(whereComboBoxes, boxes, textField, tableSelectedCurr));
						//Go to query making
						String query = getQuery();
	
							//call simpleQueryContainer3 for data display
						simpleQueryContainer3(home, conn, query);
						
						
						SwingUtilities.updateComponentTreeUI(home);
						//System.out.println("Looped Through!");
					}
				});
			}
			else{
				System.out.println("ELSE");

				tableConfirmation.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						
						home.getContentPane().removeAll();

						data.add(new queryData(whereComboBoxes, boxes, textField, tableSelectedCurr));
						//System.out.println("Looping!");
						simpleQueryContainer2(home, conn, tableSelected, iteration + 1);
						
									
						SwingUtilities.updateComponentTreeUI(home);
					}
				});
				
			}
			
			

		//////////////// END OF ACTION LISTENER ////////////////

			home.add(simpleQuery2);
		
		
		SwingUtilities.updateComponentTreeUI(home);
	}

	static void simpleQueryContainer3(JFrame home, Connection conn, String query) {

		// TODO: returns is a string containing the file version of the output.

		String file = "";

		JPanel Window = new JPanel(new GridBagLayout());
		GridBagConstraints wc = new GridBagConstraints();

		JPanel Header = new JPanel(new GridBagLayout());

		JPanel INFO = new JPanel(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();

		INFO.setBorder(new EmptyBorder(10, 10, 10, 10));
		gbc.insets = new Insets(10, 10, 10, 10);
		JLabel text = new JLabel(); // SPAGET (BusinessName duplicated when selecting businessName)
		
		for (int i = 0; i < data.size(); i++) {
			for(int j = 0; j < data.get(i).boxes.length; j++){
				if ((data.get(i)).boxes[j].isSelected() == true) {
					text = new JLabel(data.get(i).boxes[j].getText());
					if (j > 0) {
						file += "!@#$";
					}
					file += data.get(i).boxes[j].getText();
					INFO.add(text, gbc);
					//Header.add(text, gbc);
				}
			}
			file += "%^&*";
		}

		//HEADER ROW COMPLETE, MOVING TO NEXT ROW;
		gbc.gridy++;

		//////////////// QUERY DATABASE ////////////////
		try {
			final ResultSet result = conn.createStatement().executeQuery(query);
			final ResultSetMetaData resultdata = result.getMetaData();
			final int numcol = resultdata.getColumnCount();

			// OUTPUT
			// JOptionPane.showMessageDialog(null, "All information for testing from the Database.");
			while (result.next()) {
				gbc.gridy++;
				for (int i = 1; i <= numcol; i++) {
				
					if (i > 1) {
						file += "!@#$ "; //substitutes for comma
					}
				
					final String valcol = result.getString(i);

					JTextArea textArea = new JTextArea(result.getString(i));
					textArea.setLineWrap(true);
					textArea.setWrapStyleWord(true);
					textArea.setEditable(false);
					
					JPanel Cell = new JPanel();
					Cell.add(textArea);
					
					INFO.add(textArea, gbc);
										
					file += valcol;
				}
				file += "%^&*"; //substitutes for new line
			}
		} catch (final Exception e) {
			JOptionPane.showMessageDialog(null, "Error accessing Database. Possibly invalid conditions.");
			simpleQueryContainer(home, conn);
		}

		final String finalFile = file;
		//////////////// END OF QUERY DATABASE ////////////////

		JScrollPane scrollPane = new JScrollPane(INFO);
		scrollPane.setBounds(0,0,1280, 720);
		scrollPane.setColumnHeaderView(Header);
		
		wc.gridy = 0;
		wc.weighty = 1.0;
		wc.weightx = 1.0;
		wc.fill = GridBagConstraints.BOTH;
		Window.add(scrollPane, wc);

		wc.gridy = 1;
		wc.weighty = 0;
		wc.weightx = 0;
		wc.fill = GridBagConstraints.NONE;
		JButton saveToFile = new JButton("Save to File");
		saveToFile.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent a) {
			
				String filename;
				filename = JOptionPane.showInputDialog("Name of File to export");

				String returns = finalFile;

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
		});

		Window.add(saveToFile, wc);

		home.getContentPane().removeAll();
		home.add(Window, BorderLayout.CENTER);
		SwingUtilities.updateComponentTreeUI(home);
	}

	static void Question1(JFrame home, Connection conn) {
		JPanel display = new JPanel(new GridBagLayout());

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(10, 10, 10, 10);

        JLabel Name = new JLabel("Business Name");
        JLabel City = new JLabel("City");
        JLabel State = new JLabel("State");

        JTextField Name1 = new JTextField("");
        JTextField City1 = new JTextField("");
        JTextField State1 = new JTextField("");

        JTextField Name2 = new JTextField("");
        JTextField City2 = new JTextField("");
        JTextField State2 = new JTextField("");

        JButton confirm = new JButton("Confirm");

        /// HEADER ///
        gbc.gridy = 0;

        display.add(Name, gbc);
        display.add(City, gbc);
        display.add(State, gbc);

        /// ROW 1 ///
        gbc.weightx = 1.0;
        gbc.gridy++;

        display.add(Name1, gbc);
        display.add(City1, gbc);

        gbc.weightx = 0.0;

        display.add(State1, gbc);

        /// ROW 2 ///
        gbc.weightx = 1.0;
        gbc.gridy++;

        display.add(Name2, gbc);
        display.add(City2, gbc);

        gbc.weightx = 0.0;
        display.add(State2, gbc);

        /// CONFIRM ///
        gbc.gridy++;
        gbc.gridwidth = 3;
        gbc.fill = GridBagConstraints.HORIZONTAL;

        display.add(confirm, gbc);
		confirm.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String N1 = Name1.getText();
				String S1 = State1.getText();
				String C1 = City1.getText();

				String N2 = Name2.getText();
				String S2 = State2.getText();
				String C2 = City2.getText();

				System.out.println(N1 + " " + C1 + ", " + S1);
				System.out.println(N2 + " " + C2 + ", " + S2);

				String query = "SELECT \"BusinessID\" FROM \"Business\" NATURAL JOIN \"Locations\" WHERE \'Restaurants\'=ANY(\"Categories\") AND (\"Locations\".\"State\"";
				query += " = \'" + S1 + "\' AND \"Locations\".\"City\" = \'" + C1 + "\' AND \"Business\".\"BusinessName\" = \'" + N1 + "\') OR ";
				query += "(\"Locations\".\"State\" = \'" + S2 + "\' AND \"Locations\".\"City\" = \'" + C2;
				query += "\' AND \"Business\".\"BusinessName\" = \'" + N2 + "\')";

				System.out.println(query);

				Question1Query(query,conn, home);				
			}
		});

		home.add(display);
		SwingUtilities.updateComponentTreeUI(home);
	}

	static void Question1Query(String query, Connection conn, JFrame home){
		try {
			final ResultSet result = conn.createStatement().executeQuery(query);
			final ResultSetMetaData resultdata = result.getMetaData();
			final int numcol = resultdata.getColumnCount();

			result.next();
			String start = result.getString(1);
			result.next();
			String end = result.getString(1);
			// String start = "R7-3MCD6_RL_VxN65yCh2Q";
			// String end = "9kmczPRen9Ig8qbd9Tm1lw";
			
			System.out.println("Start: " + start);
			System.out.println("End: " + end);
			
			ArrayList<String[]> edges = new ArrayList<String[]>();
			//Scan file
			Scanner scanEdges = new Scanner(new File("filenames.csv"));
			while(scanEdges.hasNextLine()){
				String csvRead =  scanEdges.nextLine();
				csvRead = csvRead.replace("\"", "");
				String [] datain = csvRead.split("\\|");
				edges.add(datain);
			
			}
			scanEdges.close();
			System.out.println("prints");			
			
			HashMap<String, ArrayList<String[]>> adjacency = new HashMap<String, ArrayList<String[]>>();

			for(int i = 0; i < edges.size();i++){
				String user = edges.get(i)[0];
				String bus1 = edges.get(i)[1];
				String bus2 = edges.get(i)[2];

				if(!adjacency.containsKey(bus1)){
					adjacency.put(bus1, new ArrayList<String[]>());
					//adjacency.get(bus1).add(new String[] {bus2, user});
				}
				if(!adjacency.containsKey(bus2)){
					adjacency.put(bus2, new ArrayList<String[]>());
					//adjacency.get(bus2).add(new String[] {bus1, user});
				}

			}
			System.out.println("something appeared");
			for(int i = 0; i < edges.size();i++){
				String user = edges.get(i)[0];
				String bus1 = edges.get(i)[1];
				String bus2 = edges.get(i)[2];

				adjacency.get(bus1).add(new String[] {bus2, user});
				adjacency.get(bus2).add(new String[] {bus1, user});
			

			}
			System.out.println("something new also appeared");


			HashMap<String, String> pred = new HashMap<String, String>();
			HashMap<String, Integer> dist = new HashMap<String, Integer>();

			LinkedList<String> queue = new LinkedList<String>();
			HashMap<String, Boolean> visited = new HashMap<String, Boolean>();	
			
			adjacency.forEach((key, vertice) ->{
				visited.put(key, false);
				dist.put(key,Integer.MAX_VALUE);
				pred.put(key,null);
			});

			System.out.println("wowie");
			visited.replace(start, true);
			dist.replace(start, 0);
			queue.add(start);
			System.out.println("helloworld1");
			while(!queue.isEmpty()){
				String bus1 = queue.remove();
				ArrayList<String[]> bus2List = adjacency.get(bus1);
				//System.out.println("Size is: " + bus2List.size());
				for(int i = 0; i < bus2List.size(); i++){
					String bus2 = bus2List.get(i)[0];
					if(visited.get(bus2) == false){
						visited.replace(bus2,true);
						dist.replace(bus2, dist.get(bus1)+1);
						pred.replace(bus2,bus1);
						queue.add(bus2);

						if(bus2.equals(end)){
							System.out.println("Funished");
							break;
						}
					}
				}
				
			}
			System.out.println("helloworld2");
			LinkedList<String> path = new LinkedList<String>(); 
	  		String crawl = end; 
	    	path.add(crawl); 
			
			while (pred.get(crawl) != null){ 
				path.add(pred.get(crawl)); 
				crawl = pred.get(crawl); 
			} 
			System.out.println("helloworld3");
			// Print path 

			JPanel pathOutputs = new JPanel(new GridLayout(path.size(), 2));
			System.out.println("Business Path is ::"); 
			ArrayList<String> buildPath = new ArrayList<String>();
			String pathname = "";
			for (int i = path.size() - 1; i >= 0; i--) { 
				ResultSet pathfind = conn.createStatement().executeQuery("select \"BusinessName\" from \"Business\" where \"BusinessID\" = \'" + path.get(i) + "\'");
				while (pathfind.next())
					pathname = pathfind.getString(1);
				System.out.print(pathname + "   "); 
				JLabel pathLabel = new JLabel(pathname);
				pathOutputs.add(pathLabel);
				buildPath.add(path.get(i));
			} 
			
			ArrayList<String> userPath = new ArrayList<String>();
		
			for (int i = 0; i < buildPath.size() - 1; i++) {
				String bus1 = buildPath.get(i);
				String bus2 = buildPath.get(i + 1);
			
				ArrayList<String[]> bus2List = adjacency.get(bus1);
				String userId = "";
				for (int j = 0; j < bus2List.size(); j++) {
					if (bus2List.get(j)[0].equals(bus2)) {
						userId = bus2List.get(j)[1];
						break;
					}
				}
				userPath.add(userId);
			}
			String namepath = "";
			System.out.println("User Path is ::");
			for(int u = 0; u < userPath.size(); u++) {
				ResultSet pathfound = conn.createStatement().executeQuery("select \"Name\" from \"Users\" where \"UserID\" = \'" + userPath.get(u) + "\'");
				while (pathfound.next())
					namepath = pathfound.getString(1);
				JLabel pathLabel = new JLabel(namepath);
				pathOutputs.add(pathLabel);
				System.out.print(namepath + "   "); 
				//System.out.print(userPath.get(u) + "   ");
			}
			System.out.println();

			home.getContentPane().removeAll();
			home.add(pathOutputs);
			SwingUtilities.updateComponentTreeUI(home);
			
		} catch (final Exception e) {
			e.printStackTrace();
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			System.exit(0);
		}
		
		
			
	}
	
	static void Question2(JFrame home, Connection conn) {
		JPanel Question2Panel = new JPanel(new GridLayout(4, 1));

		JLabel displayText = new JLabel("Summarize User Reviews");
		displayText.setHorizontalAlignment(JLabel.CENTER);
		Question2Panel.add(displayText);

		JPanel instructPanel = new JPanel(new GridLayout(1, 3));
		JLabel userText = new JLabel ("Enter a user name with at least 5 reviews:");
		JLabel orText = new JLabel ("OR");
		JLabel userIDText = new JLabel ("Enter a userID with at least 5 reviews:");
		userText.setHorizontalAlignment(JLabel.CENTER);
		orText.setHorizontalAlignment(JLabel.CENTER);
		userIDText.setHorizontalAlignment(JLabel.CENTER);
		instructPanel.add(userText);
		instructPanel.add(orText);
		instructPanel.add(userIDText);
		Question2Panel.add(instructPanel);

		JPanel inputPanel = new JPanel(new GridLayout(1, 2));
		JTextField getUser = new JTextField();
		JTextField getUserID = new JTextField();
		getUser.setHorizontalAlignment(JTextField.CENTER);
		getUserID.setHorizontalAlignment(JTextField.CENTER);
		inputPanel.add(getUser);
		inputPanel.add(getUserID);
		Question2Panel.add(inputPanel);

		JButton confirmation = new JButton("OK");
		confirmation.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent a) {
				//test user Liz(MYACNxe6JzJyr0Ss1jxBbw): has 36 reviews, avg 4 stars
				//get user info
				String user = getUser.getText();
				String userID = getUserID.getText();
				String ReviewCount = "";
				String AverageRating = "";
				int usefulCount = 0;
				int funnyCount = 0;
				int coolCount = 0;
				boolean isGood = true;
				System.out.println(user);

				//query user to see if reviewcount > 4 and get avgrating
				String queryUser;
				if(!userID.equals("")){
					queryUser = "SELECT \"UserID\", \"Name\", \"ReviewCount\", \"AverageRating\" FROM \"Users\" WHERE \"Users\".\"UserID\" = \'" + userID + "\' LIMIT 1";
				}else{
					queryUser = "SELECT \"UserID\", \"Name\", \"ReviewCount\", \"AverageRating\" FROM \"Users\" WHERE \"Users\".\"Name\" = \'" + user + "\' AND  \"Users\".\"ReviewCount\" > 4 LIMIT 1";
				}
				System.out.println(queryUser);
				try {
					final ResultSet result = conn.createStatement().executeQuery(queryUser);
					result.next();

					userID = result.getString(1);
					user = result.getString(2);
					ReviewCount = result.getString(3);
					AverageRating = result.getString(4);

					System.out.println(userID + " " + user + " " + ReviewCount + " " + AverageRating);
				} catch (final Exception e) {
					JOptionPane.showMessageDialog(null, "Error: input user does not have at least 5 reviews");
					Question2(home, conn);
					isGood = false;
				}

				if(isGood){
					//query userExtra to get the yelp summary of reactions (and fans?)
					String queryUserExtra;
					queryUserExtra = "SELECT \"UserID\", \"Useful\", \"Funny\", \"Cool\" FROM \"UserExtra\" WHERE \"UserExtra\".\"UserID\" = \'" + userID + "\' LIMIT 1";
					
					try {
						final ResultSet result = conn.createStatement().executeQuery(queryUserExtra);
						result.next();
						
						usefulCount = Integer.parseInt(result.getString(2));
						funnyCount = Integer.parseInt(result.getString(3));
						coolCount = Integer.parseInt(result.getString(4));
						
						System.out.println(usefulCount + " " + funnyCount + " " + coolCount);
					} catch (final Exception e) {
						JOptionPane.showMessageDialog(null, "Error accessing Database. Possibly invalid conditions.");
						Question2(home, conn);
					}

					JFrame results = new JFrame("Results");
					JPanel resultsPanel = new JPanel(new GridLayout(2, 1));

					JLabel displayText = new JLabel(user + " : " + userID);
					displayText.setHorizontalAlignment(JLabel.CENTER);
					resultsPanel.add(displayText);

					JPanel descStatPanel = new JPanel(new GridLayout(1, 2));

					JPanel descPanel = new JPanel(new GridLayout(3, 1));
					JLabel descText = new JLabel ("Description");
					JLabel countText = new JLabel ("Total Reviews: " + ReviewCount);
					JLabel averageText = new JLabel ("Average Rating: " + AverageRating);
					descText.setHorizontalAlignment(JLabel.CENTER);
					countText.setHorizontalAlignment(JLabel.CENTER);
					averageText.setHorizontalAlignment(JLabel.CENTER);
					descPanel.add(descText);
					descPanel.add(countText);
					descPanel.add(averageText);
					descStatPanel.add(descPanel);

					JPanel statPanel = new JPanel(new GridLayout(4, 1));
					JLabel statText = new JLabel ("Statistics");
					JLabel usefulText = new JLabel ("# of useful reactions: " + usefulCount);
					JLabel funnyText = new JLabel ("# of funny reactions: " + funnyCount);
					JLabel coolText = new JLabel ("# of cool reactions: " + coolCount);
					statText.setHorizontalAlignment(JLabel.CENTER);
					usefulText.setHorizontalAlignment(JLabel.CENTER);
					funnyText.setHorizontalAlignment(JLabel.CENTER);
					coolText.setHorizontalAlignment(JLabel.CENTER);
					statPanel.add(statText);
					statPanel.add(usefulText);
					statPanel.add(funnyText);
					statPanel.add(coolText);
					descStatPanel.add(statPanel);

					resultsPanel.add(descStatPanel);
					results.add(resultsPanel);
					results.setSize(1200,700);
					results.setVisible(true);
				}
			}
		});
		Question2Panel.add(confirmation);

		home.add(Question2Panel);
		SwingUtilities.updateComponentTreeUI(home);
	}

	static void Question3(JFrame home, Connection conn) {
		JPanel Question3Panel = new JPanel(new GridLayout(3, 1));
		/// TODO: IMPLEMENT HERE ///
		
		//Question3 Text
		JLabel q3txt = new JLabel("Select a state: ");
		q3txt.setHorizontalAlignment(JLabel.CENTER);
		Question3Panel.add(q3txt);
		// Select State ComboBox
		String[] states = {"AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA", "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC", "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"};
		JComboBox<String> stateselection = new JComboBox<>(states);
		stateselection.setEditable(true);
		//stateselection.setHorizontalAlignment(JComboBox.CENTER);
		Question3Panel.add(stateselection);
		// State confirmation
		JButton confirmstate = new JButton("OK");
		Question3Panel.add(confirmstate);

		confirmstate.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent a ) {
				String userstate = stateselection.getItemAt(stateselection.getSelectedIndex());
				home.getContentPane().removeAll();

				//Sets gbc stuff
				String returns = "";
				JPanel Q3AnswerPanel = new JPanel(new GridBagLayout());
				GridBagConstraints gbc = new GridBagConstraints();
				gbc.insets = new Insets(10, 10, 10, 10);
				ArrayList<String> franchiselist = new ArrayList<String>();


				try {
					//Runs sql commands
					Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
					//System.out.println("SELECT \"BusinessName\", \"OverallRating\", \"Longitude\", \"Latitude\" FROM \"Business\" NATURAL JOIN \"Locations\" WHERE \"State\" = \'" + userstate + "\' AND \"OverallRating\" > 3.499 GROUP BY \"BusinessName\", \"OverallRating\", \"Longitude\", \"Latitude\" LIMIT 50");
					ResultSet result = conn.createStatement().executeQuery("SELECT \"BusinessName\", \"OverallRating\", \"Longitude\", \"Latitude\" FROM \"Business\" NATURAL JOIN \"Locations\" WHERE \"State\" = \'" + userstate + "\' AND \"OverallRating\" > 3.499 AND \'Restaurants\' =ANY(\"Categories\") GROUP BY \"BusinessName\", \"OverallRating\", \"Longitude\", \"Latitude\"");
					ResultSet entiredb = stmt.executeQuery("SELECT \"BusinessName\" FROM \"Business\" ");

					// get column size
					ResultSetMetaData resultstate = result.getMetaData();
					int numcol = resultstate.getColumnCount();
					gbc.gridy = 0;

					//Create arraylist specifically for franchises
					while (result.next()) {
							String busname = result.getString(1);
							int counter = 0;
							boolean isFranchise = false;
							while (entiredb.next())
							{
								if (busname.equals(entiredb.getString(1)))
								{
									counter++;
								}
								if (counter > 1)
								{
									isFranchise = true;
									//System.out.println(busname);
									break;
								}
							}
							entiredb.beforeFirst();
							if (isFranchise)
							{
								for (int i = 1; i <= numcol; i++)
								{
									franchiselist.add(result.getString(i));
								}
							}
					}
					//spaget only if more than 5 franchises in state
					if (franchiselist.size() == 0)
					{
						JOptionPane.showMessageDialog(null, "No franchises in the state.");
						System.exit(0);
					}
					if (franchiselist.size() > 20)
					{
						JPanel Cell = new JPanel();
						//get first business since it is random anyways
						for(int i = 1; i <= 4; i++){
                            JLabel textArea = new JLabel(resultstate.getColumnName(i));
                                                        
                            Cell.add(textArea);
                            
                            Q3AnswerPanel.add(textArea, gbc);

                        }
                        gbc.gridy++;
						for (int i = 0; i < 4; i++) 
						{
							JTextArea textArea = new JTextArea(franchiselist.get(i));
							textArea.setLineWrap(true);
							textArea.setWrapStyleWord(true);
							textArea.setEditable(false);
							
							Cell.add(textArea);
							
							Q3AnswerPanel.add(textArea, gbc);

						}
						int counter = 0;
						gbc.gridy++;
						ArrayList<Integer> visited = new ArrayList<Integer>();
						//name at i = 0, rating at i = 1, longitude at i = 2, latitude at i = 3, name at i = 4, etc
						int position = getDistance(franchiselist, 2, visited);
						visited.add(position);
						while (counter < 3) {
							for (int i = position-2; i < position+2; i++) {
								JTextArea textArea = new JTextArea(franchiselist.get(i));
								textArea.setLineWrap(true);
								textArea.setWrapStyleWord(true);
								textArea.setEditable(false);
								Cell.add(textArea);
								Q3AnswerPanel.add(textArea, gbc);
							}
							gbc.gridy++;
							position = getDistance(franchiselist, position, visited);
							visited.add(position);
							counter++;
						}
						for (int i = position-2; i < position+2; i++) {
							JTextArea textArea = new JTextArea(franchiselist.get(i));
							textArea.setLineWrap(true);
							textArea.setWrapStyleWord(true);
							textArea.setEditable(false);
							Cell.add(textArea);
							Q3AnswerPanel.add(textArea, gbc);
						}
					}
					else{
						JPanel Cell = new JPanel();
						for(int i = 1; i <= 4; i++){
                            JLabel textArea = new JLabel(resultstate.getColumnName(i));
                                                        
                            Cell.add(textArea);
                            
                            Q3AnswerPanel.add(textArea, gbc);

                        }
						for (int i = 0; i < franchiselist.size(); i++)
						{
							if (i > 0) {
								returns += "!@#$";
							}
							final String valcol = franchiselist.get(i);
							if (i % 4 == 0)
							{
								gbc.gridy++;
							}
							JTextArea textArea = new JTextArea(franchiselist.get(i));
							textArea.setLineWrap(true);
							textArea.setWrapStyleWord(true);
							textArea.setEditable(false);
							
							Cell.add(textArea);
							
							Q3AnswerPanel.add(textArea, gbc);
												
							returns += valcol;
						}
						returns += "%^&*";
					}

				} catch (Exception e)
				{
					JOptionPane.showMessageDialog(null, "Error accessing Database.");
					System.exit(0);
				}
				JScrollPane scrollPane = new JScrollPane(Q3AnswerPanel);
				scrollPane.setBounds(0,0,1280, 720);
				home.getContentPane().removeAll();
				home.add(scrollPane, BorderLayout.CENTER);
				SwingUtilities.updateComponentTreeUI(home);


			}
		});
		/// END IMPLEMENTATION ///
		
		home.add(Question3Panel);
		SwingUtilities.updateComponentTreeUI(home);
	}

	static void Question4(JFrame home, Connection conn) {

		JPanel Question4Panel = new JPanel(new GridLayout(4, 1));

		JLabel displayText = new JLabel("Best Local Restaurant");
		displayText.setHorizontalAlignment(JLabel.CENTER);
		Question4Panel.add(displayText);

		JLabel cityText = new JLabel ("Enter a City: ");
		cityText.setHorizontalAlignment(JLabel.CENTER);
		Question4Panel.add(cityText);

		JTextField getCity = new JTextField();
		getCity.setHorizontalAlignment(JTextField.CENTER);
		Question4Panel.add(getCity);

		JButton confirmation = new JButton("OK");
		Question4Panel.add(confirmation);

		confirmation.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				home.getContentPane().removeAll();

				SwingUtilities.updateComponentTreeUI(home);

				//loading bar maybe
				String city = getCity.getText();

				HashMap<String, Integer> restaurantsCount = new HashMap<String, Integer>();

				try {
					Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);

					ResultSet result = stmt.executeQuery("SELECT \"BusinessName\", \"BusinessID\" FROM \"Business\" WHERE 'Restaurants'=ANY(\"Categories\")"); 
					while (result.next()) {
						String key = result.getString("BusinessName");

						restaurantsCount.put(key, restaurantsCount.getOrDefault(key, 0) + 1);
					}

					ResultSet localResult = stmt.executeQuery(
						"SELECT \"Business\".\"BusinessName\", \"Business\".\"BusinessID\", \"Locations\".\"City\" FROM \"Business\" INNER JOIN \"Locations\" ON \"Business\".\"BusinessID\"=\"Locations\".\"BusinessID\" WHERE \"Locations\".\"City\"=\'" 
						+ city + "\'" + " and \'Restaurants\'=ANY(\"Business\".\"Categories\")"
					);

					int numRows = localResult.last() ? localResult.getRow() : 0;

					if (numRows == 0)  {
						// no restaurants in the given city
						int a = JOptionPane.showConfirmDialog(home, "No Restaurants Exist in the City.", "Error", JOptionPane.WARNING_MESSAGE);
						if (a == JOptionPane.YES_OPTION || a == JOptionPane.CANCEL_OPTION) {
							System.exit(1);
						}
					} 

					// local businesss that are not franchises list
					// and the respective business ids where index 0: id 1: name
					ArrayList<ArrayList<String>> localBusinesses = new ArrayList<ArrayList<String>>();

					localResult.beforeFirst();
					while (localResult.next()) {
						if (restaurantsCount.get(localResult.getString("BusinessName")) == 1) {
							ArrayList<String> tmp = new ArrayList<String>();
							tmp.add(localResult.getString("BusinessID"));
							tmp.add(localResult.getString("BusinessName"));
							localBusinesses.add(tmp);
						}
					}

					if (localBusinesses.isEmpty()) {
						int a = JOptionPane.showConfirmDialog(home, "No Local Restaurants Exist in the City", "Error", JOptionPane.WARNING_MESSAGE);
						if (a == JOptionPane.YES_OPTION || a == JOptionPane.CANCEL_OPTION) {
							System.exit(1);
						}
					}
					// find the most tipped restaurant

					HashMap<String, Integer> tipsCount = new HashMap<String, Integer>();
					
					String sql_statement = "SELECT \"Remark\", \"BusinessID\" FROM \"Customer Remarks\" WHERE \"BusinessID\" IN (VALUES ";

					if (numRows == 1) {
						sql_statement += "(\'" + localBusinesses.get(0).get(0) + "\'))";
					}
					else {
						for (int i = 0; i < localBusinesses.size() - 1; i++) {
							sql_statement += "(\'" + localBusinesses.get(i).get(0) + "\'), ";
						}
						sql_statement += "(\'" + localBusinesses.get(localBusinesses.size() - 1).get(0) + "\'))";
					}
					

					ResultSet remarksTmpResultSet = stmt.executeQuery(sql_statement);

					while (remarksTmpResultSet.next()) {
						String key = remarksTmpResultSet.getString("BusinessID");

						tipsCount.put(key, tipsCount.getOrDefault(key, 0) + 1);
					}

					HashMap.Entry<String, Integer> maxEntry = null;
					for (HashMap.Entry<String, Integer> entry : tipsCount.entrySet()) {
						if (maxEntry == null || entry.getValue().compareTo(maxEntry.getValue()) > 0) {
							maxEntry = entry;
						}
					}

					String bestRestaurant = "";

					for (int i = 0; i < localBusinesses.size(); i++) {
						if (localBusinesses.get(i).get(0).equals(maxEntry.getKey())) {
							bestRestaurant = localBusinesses.get(i).get(1);
							break;
						}
					}

					String bestRestaurantID = maxEntry.getKey();

					// output the results
					home.getContentPane().removeAll();

					JPanel output = new JPanel(new GridBagLayout());
					GridBagConstraints c = new GridBagConstraints();
					c.gridx = 0;
					c.gridy = 0;
					c.insets = new Insets(10, 10, 10, 10);
					JLabel bestRestaurantJLabel = new JLabel(bestRestaurant);
					output.add(bestRestaurantJLabel);
					
					remarksTmpResultSet.beforeFirst();
					while (remarksTmpResultSet.next()) {
						if (remarksTmpResultSet.getString("BusinessID").equals(bestRestaurantID)) {
							c.gridy++;

							JTextArea textArea = new JTextArea(remarksTmpResultSet.getString("Remark"));

							textArea.setLineWrap(true);
							textArea.setWrapStyleWord(true);
							textArea.setEditable(false);

							output.add(textArea, c);
						}
					}
					JScrollPane sp = new JScrollPane(output);
					sp.setBounds(0, 0, 1280, 720);

					home.add(sp);
					SwingUtilities.updateComponentTreeUI(home);

				} catch (Exception question4Error) {
					System.out.println(question4Error);
					System.exit(1);
				}

			}
		});

		home.add(Question4Panel);
		SwingUtilities.updateComponentTreeUI(home);
	}
	
	static void Question5(JFrame home, Connection conn) {
		JPanel Question5Panel = new JPanel(new GridLayout(5, 1));

		JLabel q5state = new JLabel("Enter a State: ");
		q5state.setHorizontalAlignment(JLabel.CENTER);
		Question5Panel.add(q5state);

		JTextField getState = new JTextField();
		getState.setHorizontalAlignment(JTextField.CENTER);
		Question5Panel.add(getState);

		JLabel q5city = new JLabel("Enter a City: ");
		q5city.setHorizontalAlignment(JTextField.CENTER);
		Question5Panel.add(q5city);

		JTextField getCity = new JTextField();
		getCity.setHorizontalAlignment(JTextField.CENTER);
		Question5Panel.add(getCity);

		JButton confirmation = new JButton("OK");
		Question5Panel.add(confirmation);

		confirmation.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent a) {
				home.getContentPane().removeAll();
				String city = getCity.getText();
				String state = getState.getText();

				String returns = "";
				JPanel Q5AnswerPanel = new JPanel(new GridBagLayout());
				GridBagConstraints gbc = new GridBagConstraints();
				gbc.insets = new Insets(10, 10, 10, 10);

				try {
					Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
					Statement stmt1 = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
					
					//Obtain total number of customer remarks and reviews	
					ResultSet totalremarks = conn.createStatement().executeQuery("SELECT count(*) FROM \"Customer Remarks\"");
					ResultSet totalreviews = conn.createStatement().executeQuery("SELECT count(*) as exact_count from \"Customer Reviews\"");
					ResultSet cusreviews = stmt1.executeQuery("SELECT \"BusinessID\" FROM \"Customer Reviews\"");
					ResultSet cusremarks = stmt.executeQuery("SELECT \"BusinessID\" FROM \"Customer Remarks\"");
					ResultSet citybus = conn.createStatement().executeQuery("SELECT \"BusinessName\", \"BusinessID\", \"OverallRating\" FROM \"Business\" NATURAL JOIN \"Locations\" WHERE \"State\" = \'" + state + "\' AND \"City\" = \'" + city + "\'");
					totalreviews.next();
					totalremarks.next();
					int remarkrows = totalremarks.getInt(1);
					int reviewrows = totalreviews.getInt(1);

					//get total reviews and remarks
					int totalamount = remarkrows + reviewrows;
					gbc.gridy = 0;
					//variables for most popular business
					double maxrating = 0;
					String maxname = "";
					String maxid = "";
					int reviewtotal = 0;
					double busrate = 0;
					while (citybus.next()) {
						String reviewid = citybus.getString(2);
						//numreviews is total remarks and reviews for a businessid
						int numreviews = 0;
						while (cusremarks.next())
						{
							if (reviewid.equals(cusremarks.getString(1)))
							{
								numreviews++;
							}
						}
						while (cusreviews.next())
						{
							if (reviewid.equals(cusreviews.getString(1)))
							{
								numreviews++;
							}
						}
						double busrating = citybus.getDouble(3);
						double totalrating = (double)(numreviews/totalamount) * 0.7 + busrating * 0.3;
						if (totalrating > maxrating)
						{
							maxname = citybus.getString(1);
							maxid = citybus.getString(2);
							maxrating = totalrating;
							reviewtotal = numreviews;
							busrate = busrating;
						}
						cusreviews.beforeFirst();
						cusremarks.beforeFirst();

					}
					if (maxname == "" && maxid == "")
					{
						JOptionPane.showMessageDialog(null, "The city chosen does not contain businesses.");
						System.exit(0);
					}
					//Output
					JPanel Cell = new JPanel();
					//Get header
					JLabel idlabel = new JLabel("BusinessID");
					Cell.add(idlabel);
					Q5AnswerPanel.add(idlabel, gbc);

					JLabel namelabel = new JLabel("BusinessName");
					Cell.add(namelabel);
					Q5AnswerPanel.add(namelabel, gbc);

					JLabel revlabel = new JLabel("Number of Reviews");
					Cell.add(revlabel);
					Q5AnswerPanel.add(revlabel, gbc);

					JLabel ratinglabel = new JLabel("Overall Rating");
					Cell.add(ratinglabel);
					Q5AnswerPanel.add(ratinglabel, gbc);

					gbc.gridy++;
					//Get most popular business
					JTextArea popid = new JTextArea(String.valueOf(maxid));
					popid.setLineWrap(true);
					popid.setWrapStyleWord(true);
					popid.setEditable(false);
					Cell.add(popid);
					Q5AnswerPanel.add(popid, gbc);

					JTextArea popname = new JTextArea(String.valueOf(maxname));
					popname.setLineWrap(true);
					popname.setWrapStyleWord(true);
					popname.setEditable(false);
					Cell.add(popname);
					Q5AnswerPanel.add(popname, gbc);

					JTextArea poprev = new JTextArea(String.valueOf(reviewtotal));
					poprev.setLineWrap(true);
					poprev.setWrapStyleWord(true);
					poprev.setEditable(false);
					Cell.add(poprev);
					Q5AnswerPanel.add(poprev, gbc);

					JTextArea poprating = new JTextArea(String.valueOf(busrate));
					poprating.setLineWrap(true);
					poprating.setWrapStyleWord(true);
					poprating.setEditable(false);
					Cell.add(poprating);
					Q5AnswerPanel.add(poprating, gbc);

				}
				catch (Exception e)
				{
					JOptionPane.showMessageDialog(null, "Error accessing Database.");
					System.exit(0);
				}
				JScrollPane scrollPane = new JScrollPane(Q5AnswerPanel);
				scrollPane.setBounds(0,0,1280, 720);
				home.getContentPane().removeAll();
				home.add(scrollPane, BorderLayout.CENTER);
				SwingUtilities.updateComponentTreeUI(home);
			}
		});

		home.add(Question5Panel);
		SwingUtilities.updateComponentTreeUI(home);
	}
	
	public static void main(final String args[]) {

		// Establishing a connection
		final dbSetup my = new dbSetup(); // credentials
		Connection conn = null;
		try {
			Class.forName("org.postgresql.Driver");
			conn = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/db909_group4_project2",
					my.user, my.pswd);
		} catch (final Exception e) {
			e.printStackTrace();
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			System.exit(0);
		}

		try {
			final Statement stmt = conn.createStatement();

			/**
			 * Home Window
			 */
			JFrame home = new JFrame("JDBC");
			home.setLayout(new BorderLayout());
			home.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
			
			// Home Windows Constraints
			home.setSize(1200,700); // Home Window Size
			home.setVisible(true); //making the frame visible
			/** 
				End Home Window
			*/

			homeMenu(home, conn);

		} catch (final Exception e) {
			System.out.println(e);
		}
  	}//end main
}//end Class
