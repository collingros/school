/*
collin gros
05-05-2021
cs-482
Project Phase 2


heavily referenced:
    (GUI):
        https://docs.oracle.com/javase/tutorial/uiswing/components/button.html
        https://docs.oracle.com/javase/tutorial/uiswing/components/textfield.html
        https://docs.oracle.com/javase/tutorial/uiswing/components/dialog.html
    (java and MYSQL):
        https://stackoverflow.com/questions/2839321/connect-java-to-a-mysql-database
        https://stackoverflow.com/questions/5809239/query-a-mysql-db-using-java
        https://techblogstation.com/java/read-text-file-in-java/
*/

// gui
import javax.swing.AbstractButton;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.ImageIcon;
import javax.swing.JTextField;
import javax.swing.JTextArea;
import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

// mysql
import java.sql.*;

// file reading
import java.io.*;
//import java.io.BufferedReader;
//import java.io.File;
//import java.io.FileReader;


public class DatabaseGUI extends JPanel
                        implements ActionListener
{
    // width/height of window created
    static int FRAME_WIDTH = 640;
    static int FRAME_HEIGHT = 480;
    // maximum length of character path
    static int MAX_PATH_LEN = 20;

    // mysql connection variables
    static String JDBC_URL = "jdbc:mysql://localhost:3306/javabase";
    static String USER = "root";
    static String PASSWORD = "blah";

    // buttons for bulk loading, single insertion, and deletion
    protected JButton binsert, sinsert, query, delete;
    protected JTextField text;
    protected JFrame frame;

    public DatabaseGUI(JFrame frame)
    {
        this.frame = frame;

        // create buttons for insertion/deletion
        binsert = new JButton("Bulk Loading");
        binsert.setVerticalTextPosition(AbstractButton.CENTER);
        binsert.setHorizontalTextPosition(AbstractButton.LEADING); //aka LEFT, for left-to-right locales
        binsert.setActionCommand("binsert_pressed");

        sinsert = new JButton("Single Insertion");
        sinsert.setVerticalTextPosition(AbstractButton.CENTER);
        sinsert.setHorizontalTextPosition(AbstractButton.LEADING); //aka LEFT, for left-to-right locales
        sinsert.setActionCommand("sinsert_pressed");

        query = new JButton("Query");
        query.setHorizontalTextPosition(AbstractButton.CENTER);
        query.setActionCommand("query_pressed");

        delete = new JButton("Delete Table");
        delete.setHorizontalTextPosition(AbstractButton.CENTER);
        delete.setActionCommand("delete_pressed");

        binsert.addActionListener(this);
        sinsert.addActionListener(this);
        query.addActionListener(this);
        delete.addActionListener(this);



       // create text fields for dataset path
        text = new JTextField(MAX_PATH_LEN);
        text.addActionListener(this);

        // area for textfield to sit in


        add(text);
        add(binsert);
        add(sinsert);
        add(query);
        add(delete);
    }


    public static void genRandomData(String text, int maxLines, String t)
    {
        try {
            // prepare for writing the file
            File file = new File(text);
            FileWriter fw = new FileWriter(file);
            BufferedWriter bw = new BufferedWriter(fw);

            String output = "";

            // generate the data
            if (t.equals("players")) {
                // players table data
                int minTouch = 10;
                int minYards = 100;
                int minSalary = 100000;
                String[] positions = {"QB", "RB", "WR"};
                for (int i = 0; i < maxLines; ++i) {
                    String line = "\'Name" + (maxLines-i) +"\',"
                        + i + ","
                        + "\'Team" + i%2 + "\',"
                        + "\'" + positions[i%3] + "\',"
                        + (minTouch+i) + ","
                        + (minYards+i) + ","
                        + (minSalary+i) + "\n";

                    output +=  line;
                }
            }
            else if (t.equals("games")) {
                // games table data
                int att = 100;
                int ticket = 100000;
                String[] result = {"W", "L", "T"};
                for (int i = 0; i < maxLines; ++i) {
                    String line = i + ","
                        + "\'200" + (i%9) + "-11-11\',"
                        + "\'Stadium" + i%2 + "\',"
                        + "\'" + result[i%3] + "\',"
                        + (att+i) + ","
                        + (ticket+i) + "\n";

                    output +=  line;
                }
            }
            else if (t.equals("play")) {
                // play table data
                int att = 100;
                int ticket = 100000;
                String[] result = {"W", "L", "T"};
                for (int i = 0; i < maxLines; ++i) {
                    String line = i + "," + i + "\n";

                    output +=  line;
                }
            }

            // write data to file
            bw.write(output);
            bw.close();
        }
        // exception handling
        catch (FileNotFoundException e) {
                System.out.println("ERROR: file  does not exist!");
        }
        catch (IOException e) {
                System.out.println("ERROR: IOException");
        }
    }


    // given the path to the data file, reads data and stores
    // in a 2D String array
    //
    // returns null if failed
    public String[][] readData(String text)
    {
        String[][] data = null;
        try {
            // prepare for reading the file
            File file = new File(text);
            BufferedReader br = new BufferedReader(new FileReader(file));


            // open once to get number of rows, columns
            String line;
            int i = 0, j = 0;
            // get column count and row count
            while ((line = br.readLine()) != null) {
                if (i == 0) {
                    String[] lineSplit = line.split(",");
                    j = lineSplit.length;
                    ++i;
                }
                else {
                        ++i;
                }
            }

            // create new String[][] from number of rows/cols in file
            data = new String[i][j];

            // begin reading
            i = 0;
            // reset position in file by creating a new buffered reader
            // (unfortunately)
            br = new BufferedReader(new FileReader(file));
            while ((line = br.readLine()) != null) {
                // split line by , to process with SQL query
                String[] lineSplit = line.split(",");
                // skip lines that do not have columns consistent with first
                // row
                if (lineSplit.length != j) {
                    continue;
                }

                // assign columns to row of data, then go on to the next
                data[i] = lineSplit;
                ++i;
            }

        }
        // exception handling
        catch (FileNotFoundException e) {
            JOptionPane.showMessageDialog(frame,
                "ERROR: file \"" + text + "\" does not exist!"
            );
        }
        catch (IOException e) {
            JOptionPane.showMessageDialog(frame,
                "ERROR: IOException"
            );
        }

        return data;
    }


    public String getTableName(String text)
    {
        String[] textSplit = text.split("\\\\");
//        String[] textSplit = text.split("/");
        String tableNameExt = textSplit[textSplit.length-1];
        // remove '.txt' extension
        String[] tableNameSplit = tableNameExt.split("\\.");
        String tableName = tableNameSplit[0];

        return tableName;
    }


    // called when sinsert button is pressed. text from text field is
    // given to this function
    //
    // returns -1 if error
    public double sinsert(String text)
    {
        long startTime, endTime;
        double durationSeconds;

        // set for errors
        durationSeconds = -1;

        // begin timer
        startTime = System.nanoTime();

        // get table name
        String tableName = getTableName(text);
        // get all the data from the file in a 2D array
        String[][] data = readData(text);
        // if we failed to read data
        if (data == null) {
            return durationSeconds;
        }



        // insert iteratively
        String insertMysql = "";
        for (int i = 0; i < data.length; ++i) {
            // insert into command
            insertMysql = "INSERT INTO "
                + tableName
                + " VALUES (";
            for (int j = 0; j < data[0].length; ++j) {
                // if/else conditional for controlling comma placement
                if (j == 0) {
                    insertMysql += data[i][j];
                }
                else {
                    insertMysql += "," + data[i][j];
                }
            }
            insertMysql += ");";

            // execute mysql
            query(insertMysql, true);
        }


        endTime = System.nanoTime();
        // convert nanoseconds to seconds
        durationSeconds = (endTime - startTime) / 1e9;

        return durationSeconds;
    }


    // called when binsert button is pressed. text from text field is
    // given to this function
    public double binsert(String text)
    {
        long startTime, endTime;
        double durationSeconds;

        // error if returned -1
        durationSeconds = -1;

        // begin timer
        startTime = System.nanoTime();

        // get table name
        String tableName = getTableName(text);
        // bulk load command
        String binsertMysql = "LOAD DATA INFILE \'"
            + text +"\' INTO TABLE "
            + tableName + " FIELDS TERMINATED BY \',\' "
            + "OPTIONALLY ENCLOSED BY \'\'\'\' LINES TERMINATED BY \'\\n\';";

        // execute bulk insert
        query(binsertMysql, true);

        endTime = System.nanoTime();
        // convert nanoseconds to seconds
        durationSeconds = (endTime - startTime) / 1e9;

        return durationSeconds;
    }


    // called when query button is pressed. text from text field is
    // given to this function, and executed a call as determined by below:
    //     isUpdate determines whether or not to call
    //     Statement.executeQuery() vs Statement.executeUpdate().
    public double query(String text, boolean isUpdate)
    {
        long startTime, endTime;
        double durationSeconds;

        endTime = -1;

        // begin timer
        startTime = System.nanoTime();


        // SQLException requires this try-catch block to get the SQL error
        // if there is one
        String output = "";
        int res = 0;
        try {
            // attempt connection
            Connection conn = DriverManager.getConnection(JDBC_URL, USER, PASSWORD);

            Statement stmt = conn.createStatement();
            // execute query and get result
            //System.out.println("executing: \"" + text + "\"");

            // decide if we should call executeQuery or executeUpdate.
            ResultSet rs = null;
            // executeUpdate. gets an integer representing num rows affected.
            if (isUpdate) {
                res = stmt.executeUpdate(text);
            }
            // executeQuery instead. gets a resulting set which is output
            else {
                rs = stmt.executeQuery(text); 
                // parse result
                while (rs.next()) {
                    int numColumns = rs.getMetaData().getColumnCount();
                    for (int i = 1; i <= numColumns; ++i) {
                        output += rs.getObject(i) + "\t";
                    }
                    output += "\n";
                }
            }
        }
        catch (SQLException e) {
            // stop timer
            endTime = System.nanoTime();
            JOptionPane.showMessageDialog(frame,
                "ERROR: SQLException Code: " + e.getErrorCode()
            );
        }

        // stop timer
        if (endTime == -1) {
            endTime = System.nanoTime();
        }
        // convert nanoseconds to seconds
        durationSeconds = (endTime - startTime) / 1e9;

        if (isUpdate) {
            // show number of rows affected
            /*
            JOptionPane.showMessageDialog(frame,
                new JTextArea("Number of rows affected: " + res)
            );
            */
        }
        else {
            // show the retrieved output
            JOptionPane.showMessageDialog(frame,
                new JTextArea("----RETRIEVED OUTPUT----\n" + output)
            );
        }

        return durationSeconds;
    }


    // called when delete button is pressed. text from text field is
    // given to this function
    public double delete(String text)
    {
        long startTime, endTime;
        double durationSeconds;

        startTime = System.nanoTime();
        // get table name
        String tableName = getTableName(text);

        // mysql delete command
        String deleteStr = "DELETE FROM " + tableName + ";";

        query(deleteStr, true);

        endTime = System.nanoTime();
        // convert nanoseconds to seconds
        durationSeconds = (endTime - startTime) / 1e9;

        return durationSeconds;
    }


    public void actionPerformed(ActionEvent e) {
        // give execution time for each event
        double durationSeconds = 0;

        if ("binsert_pressed".equals(e.getActionCommand())) {
            durationSeconds = binsert(text.getText());
        }
        else if ("sinsert_pressed".equals(e.getActionCommand())) {
            durationSeconds = sinsert(text.getText());
        }
        else if ("query_pressed".equals(e.getActionCommand())) {
            durationSeconds = query(text.getText(), false);
        }
        else if ("delete_pressed".equals(e.getActionCommand())) {
            durationSeconds = delete(text.getText());
        }


        // tell user execution time
        JOptionPane.showMessageDialog(frame,
            "execution time: " + durationSeconds
        );
    }


    private static void createAndShowGUI() {

        //Create and set up the window.
        JFrame frame = new JFrame("DatabaseGUI");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        DatabaseGUI newContentPane = new DatabaseGUI(frame);
        newContentPane.setOpaque(true); //content panes must be opaque
        frame.setContentPane(newContentPane);

        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }


    // generates all sets of random data for each table type
    public static void genAllRandomData()
    {
        String[] locs = {"./data/100/",
            "./data/150/",
            "./data/200/"};
        int[] maxLines = {100000, 150000, 200000};
//        String[] types = {"players", "games", "play"};
        String[] types = {"games"};
        for (int i = 0; i < types.length; ++i) {
            for (int j = 0; j < locs.length; ++j) {
                String curLoc = locs[j] + types[i] + ".txt";
                genRandomData(curLoc, maxLines[j], types[i]);
            }
        }

    }


    // deletes all data from all tables
    public void deleteAll(String[] types )
    {
        for (int j = 0; j < types.length; ++j) {
            delete(types[j]);
        }

    }


    // tests each function for each dataset and gets a runtime for each (only players.txt)
    public void printAllRunningTimes()
    {
        String root = "C:\\\\ProgramData\\\\MySQL\\\\MySQL Server 8.0\\\\Uploads\\\\data";
        String[] sizes = {"100", "150", "200"};

        for (int i = 0; i < sizes.length; ++i) {
            String curLoc = root
                + "\\\\" + sizes[i]
                + "\\\\" + "players.txt";
            delete(curLoc);
            // save time for bulk insertion
            //double timeBinsert = binsert(curLoc);
            // save time for single insertion

            double timeSinsert = sinsert(curLoc);
            double timeBinsert = 0;
            // print results
            System.out.println("location:\t" + curLoc
                + "\nresult(S):\t" + timeSinsert
                + "\nresult(B):\t" + timeBinsert
                +"\n");
        }

    }


    public static void main(String[] args)
    {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                //genAllRandomData();
                createAndShowGUI(); 
            }
        });
    }
}







