import java.sql.*;
import java.awt.*;
import java.util.List;
import java.io.FileWriter;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import java.awt.GridBagConstraints;  
import java.awt.GridBagLayout; 
import java.awt.event.*;

public class queryData  {
    public ArrayList<JComboBox<String>> whereComboBoxes;
    public JCheckBox boxes[];
    public JTextField textField[];
    String tableSelected;
    
    public queryData(ArrayList<JComboBox<String>> whereComboBoxes, JCheckBox boxes[], JTextField textField[], String tableSelected) {
      this.whereComboBoxes = whereComboBoxes;
      this.boxes = boxes;
      this.textField = textField;
      this.tableSelected = tableSelected;
    }
}
  