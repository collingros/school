// Collin Gros, Grant Hall, Andrew Harper, Ronak Joshi (G4)
// 04/27/19
// CS-2365-001
// Project

/*
Question. Create a Account class (fields private: Customer , int id(100, 101,…), char accountType i.e ‘C’ for current &‘S’ for saving accounts, double balance (hard-coded values). Provide get & set methods and parameterize & non-parameterize constructors. Also provide withdaw(double amount) & deposit(double amount) methods and displayBalance( ) and displayAll( ) method. Consult lecture#9 for this Assignment.

//displayAll( ) prints all instance variables
Create a Customer class (Instance Variables: private: String strLName ; private String strFName Methods: public get Methods & parameterize constructor)

Create a SavingsAccount class inheriting from Account class. SavingsAccount class (Instance Variables: private: double rate ; Methods: public addInterest(…), deductLoan(…), parameterize constructor) 

Note for simplicity, assume that SavingAccount class is managing both Saving (i.e. accountType =’s’) and Current ( i.e. accountType = ‘c’) accounHolders.

The first line of derived class constructor should invoke the base class constructor using super and then provide code to initialize the local instance variables. You can hard-code the values also. 

Now create a class UseSavingBankAccount class which incorporates GUI components like Menus, MenuItems and Dialog Boxes. Create 50 array of objects for SavingAccount class and 50 array of objects of Customer class using  parameterize constructors. Use a ‘for’ loop to create array of objects. Now provide a menu “Options”: 
*/

/*
group specific:

And four menuItems (title of one of the menu items is same as operations in one of the sub-questions 13, 14, 15 & 15b and the other is “exit” ). Each menuitem launches a dialog box (i.e. dlgbox1, dlgbox2, dlgbox3, dlgbox4). GUI components in each dialog box are (created programmatically, see sample application on the blackboard and) described below: 

Based upon the subquestion selected; choose the label and text fields:

four labels (id: dlgBox1, id & rate:dlgBox2 , and AccountType:dlgBox3), four text fields (to input id: dlgBox1, to input id & rate:dlgBox2, and to input AccType:dlgBox3) and a “submit” push Button (in each dlgBox) for the following four operations:

(13) Delete an account by id. Provide a method deleteAnAccountById(SavingAccount[], int)
(14) Delete an account by Name. Provide a method deleteAnAccountByName(SavingAccount[ ], String)
(15)  Display all Customer’s information Sorted by name; Provide method sortByName(SavingAccount[ ]) and then call displayAll() (15b): Exit
*/
import javax.swing.*;
import java.util.*;


class Account
{
    private int id;
    private char type;
    private double balance;
    private Customer cust;

    Account()
    {
        id = 0;
        type = 's';
        balance = 0.0;
        cust = new Customer("default", "default");
    }

    Account(int id, char type, double balance, Customer cust)
    {
        this.id = id;
        this.type = type;
        this.balance = balance;
        this.cust = cust;
    }

    public String get_name()
    {
        String fname = cust.get_fname();
        String lname = cust.get_lname();
        String full = fname + " " + lname;

        return full;
    }
    
    public int get_id()
    {
        return id;
    }

    public char get_type()
    {
        return type;
    }

    public double get_balance()
    {
        return balance;
    }

    public Customer get_cust()
    {
        return cust;
    }

    public void withdraw(double amount)
    {
        balance -= amount;
    }

    public void deposit(double amount)
    {
        balance += amount;
    }

    public void display_balance()
    {
        System.out.println(balance);
    }

    public void display_all()
    {
        String first = cust.get_fname();
        String last = cust.get_lname();
        System.out.println(first + " " + last);

        System.out.println(id);
        System.out.println(type);
        System.out.println(balance);
    }
}


class SavingAccount extends Account
{
    private double rate;

    SavingAccount(int id, char type, double balance,
                  double rate, Customer cust)
    {
        super(id, type, balance, cust);
        this.rate = rate;
    }

    public void add_interest()
    {
        deposit(rate);
    }

    public void deduct_loan()
    {
        withdraw(rate);
    }
}


class UseSavingBankAccount {
    public SavingAccount[] accounts;
    public Customer[] custs;

    public UseSavingBankAccount()
    {
        accounts = new SavingAccount[50];
        custs = new Customer[50];

        char type;
        double balance = 2;
        double rate = 100;

        for (int i = 0; i < 50; i++) {
            String first = "CUSTF" + i;
            String last = "CUSTL" + i;
            Customer cust = new Customer(first, last);

            if (i % 2 == 0)
                type = 'c';
            else
                type = 's';

            balance += i;

            rate *= 0.5;

            accounts[i] = new SavingAccount(i, type, balance, rate, cust);
            custs[i] = cust;
        }
    }

    public SavingAccount[] deleteAnAccountById(SavingAccount[] accs,
                                           int target)
    {
        SavingAccount[] new_accs = new SavingAccount[accs.length-1];

        boolean found = false;
        for (int i = 0; i < accs.length; i++) {
            SavingAccount acc = accs[i];

            if (acc.get_id() == target) {
                found = true;
                continue;
            }
            if (found) {
                new_accs[i-1] = acc;
            }
            else {
                new_accs[i] = acc;
            }
        }

        return new_accs;
    }

    public SavingAccount[] deleteAnAccountByName(SavingAccount[] accs, String target)
    {
        SavingAccount[] new_accs = new SavingAccount[accs.length - 1];

        boolean found = false;
        for (int i = 0; i < accs.length; i++) {
            SavingAccount acc = accs[i];

            if (acc.get_name().equals(target)) {
                found = true;
                continue;
            }
            if (found) {
                new_accs[i-1] = acc;
            }
            else {
                new_accs[i] = acc;
            }
        }

        return new_accs;
    }

    public SavingAccount getSavingAccountByName(SavingAccount[] accs,
                                                String name)
    {
        SavingAccount account = null;
        for (SavingAccount acc : accs) {
            if (acc.get_name().equals(name)) {
                account = acc;
            }
        }

        return account;
    }

    public void sortByName(SavingAccount[] accs)
    {
        SavingAccount[] sorted = accs.clone();
        String[] names = new String[accs.length];

        for (int i = 0; i < accs.length; i++) {
            SavingAccount acc = accs[i];
            String name = acc.get_name();

            names[i] = name;
        }

        Arrays.sort(names);

        for (int i = 0; i < accs.length; i++) {
            String name = names[i];
            SavingAccount acc = getSavingAccountByName(accs, name);

            sorted[i] = acc;
        }

        for (SavingAccount acc : sorted) {
            acc.display_all();
        }
    }
}


class Customer
{
    private String fname;
    private String lname;

    Customer(String fname, String lname)
    {
        this.fname = fname;
        this.lname = lname;
    }

    public String get_fname()
    {
        return fname;
    }

    public String get_lname()
    {
        return lname;
    }
}


public class GrosHallHarperJoshi extends javax.swing.JFrame {

    /**
     * Creates new form Frame
     */

    private boolean mb_1_act = false;
    private boolean mb_2_act = false;
    private boolean mb_3_act = false;

    UseSavingBankAccount bank = new UseSavingBankAccount();

    public GrosHallHarperJoshi() {
        initComponents();
        
        text_1.setVisible(false);
        label_1.setVisible(false);
        but_1.setVisible(false);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        dialog_1 = new javax.swing.JDialog();
        jSeparator1 = new javax.swing.JSeparator();
        text_1 = new javax.swing.JTextField();
        label_1 = new javax.swing.JLabel();
        but_1 = new javax.swing.JButton();
        jMenuBar1 = new javax.swing.JMenuBar();
        m_file = new javax.swing.JMenu();
        mb_1 = new javax.swing.JMenuItem();
        mb_2 = new javax.swing.JMenuItem();
        mb_3 = new javax.swing.JMenuItem();
        m_exit = new javax.swing.JMenu();

        javax.swing.GroupLayout dialog_1Layout = new javax.swing.GroupLayout(dialog_1.getContentPane());
        dialog_1.getContentPane().setLayout(dialog_1Layout);
        dialog_1Layout.setHorizontalGroup(
            dialog_1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 400, Short.MAX_VALUE)
        );
        dialog_1Layout.setVerticalGroup(
            dialog_1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 300, Short.MAX_VALUE)
        );

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        text_1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                text_1ActionPerformed(evt);
            }
        });

        label_1.setText("ID");

        but_1.setText("OK");
        but_1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                but_1ActionPerformed(evt);
            }
        });

        m_file.setText("File");

        mb_1.setText("Delete Account by ID");
        mb_1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                mb_1ActionPerformed(evt);
            }
        });
        m_file.add(mb_1);

        mb_2.setText("Delete Account by Name");
        mb_2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                mb_2ActionPerformed(evt);
            }
        });
        m_file.add(mb_2);

        mb_3.setText("Display All Sorted by Name");
        mb_3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                mb_3ActionPerformed(evt);
            }
        });
        m_file.add(mb_3);

        jMenuBar1.add(m_file);

        m_exit.setText("Exit");
        m_exit.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                m_exitMouseClicked(evt);
            }
            public void mousePressed(java.awt.event.MouseEvent evt) {
                m_exitMousePressed(evt);
            }
        });
        jMenuBar1.add(m_exit);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap(26, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(label_1)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(text_1, javax.swing.GroupLayout.PREFERRED_SIZE, 82, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(87, 87, 87))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(but_1)
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(text_1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(label_1))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(but_1)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void m_exitMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_m_exitMouseClicked
        System.exit(0);
    }//GEN-LAST:event_m_exitMouseClicked

    private void mb_1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_mb_1ActionPerformed
        mb_1_act = true;
        mb_2_act = false;
        mb_3_act = false;
        
        but_1.setVisible(true);
        text_1.setVisible(true);
        label_1.setVisible(true);
        label_1.setText("ID");
    }//GEN-LAST:event_mb_1ActionPerformed

    private void mb_2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_mb_2ActionPerformed
        mb_1_act = false;
        mb_2_act = true;
        mb_3_act = false;
        
        but_1.setVisible(true);
        text_1.setVisible(true);
        label_1.setVisible(true);
        label_1.setText("Name");
    }//GEN-LAST:event_mb_2ActionPerformed

    private void mb_3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_mb_3ActionPerformed
        mb_1_act = false;
        mb_2_act = false;
        mb_3_act = true;
        
        but_1.setVisible(true);
        text_1.setVisible(false);
        label_1.setVisible(false);
        label_1.setText("Sort");
    }//GEN-LAST:event_mb_3ActionPerformed

    private void m_exitMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_m_exitMousePressed
        System.exit(0);
    }//GEN-LAST:event_m_exitMousePressed

    private void text_1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_text_1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_text_1ActionPerformed

    private void but_1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_but_1ActionPerformed
        if (mb_1_act) {
            int id = Integer.parseInt(text_1.getText());

            SavingAccount[] accs = bank.deleteAnAccountById(bank.accounts, id);
            bank.accounts = accs;
        }
        else if (mb_2_act) {
            String name = text_1.getText();
            
            SavingAccount[] accs = bank.deleteAnAccountByName(bank.accounts,
                                                              name);
            bank.accounts = accs;
        }
        else if (mb_3_act) {
            bank.sortByName(bank.accounts);
        }
    }//GEN-LAST:event_but_1ActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new GrosHallHarperJoshi().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton but_1;
    private javax.swing.JDialog dialog_1;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JLabel label_1;
    private javax.swing.JMenu m_exit;
    private javax.swing.JMenu m_file;
    private javax.swing.JMenuItem mb_1;
    private javax.swing.JMenuItem mb_2;
    private javax.swing.JMenuItem mb_3;
    private javax.swing.JTextField text_1;
    // End of variables declaration//GEN-END:variables
}
