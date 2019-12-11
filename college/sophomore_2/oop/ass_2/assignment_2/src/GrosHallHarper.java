// Collin Gros, Grant Hall, Andrew Harper (G4)
// 04/08/19
// CS-2365-001
// Assignment 2

/*
Question. Create a BankAccount class (fields private: String strName (TTU1, TTU2,..), int id(100, 101,…),
char accountType i.e ‘C’ for current &‘S’ for saving accounts, double balance (hard-coded values).
Provide get & set methods and parameterize & non-parameterize constructors. Also provide withdaw(double amount)
& deposit(double amount) methods and displayBalance( ) and displayAll( ) method.

//displayAll( ) prints all instance variables

Create a SavingAccount class inheriting from Account class. SavingAccount class
(Instance Variables: private: double rate ; Methods: public addInterest(…), deductLoan(…), parameterize constructor)

Note for simplicity, assume that SavingAccount class is managing both Saving
(i.e. accountType =’s’) and Current ( i.e. accountType = ‘c’) accounHolders.

The first line of derived class constructor should invoke the base class constructor using super and
then provide code to initialize the local instance variables.. You can hard-code the values also.

Now create a class UseSavingBankAccount class which incorporates GUI components. Create 50 array of objects for SavingAccount class using
parameterize constructors.. Use a ‘for’ loop to create array of objects. Now provide radio button to perform following operations .
*/

/*
group specific:

G4 (Collin, Grant, Andrew) G12(Marie, Leslye, Trisha), G19(Anil, Santosh, Blaine)
Provide four radio Buttons (title same as operations in the question), three labels (id, id, accountType), three text fields
(to input id, again to input id and to input accountType) and a “submit” push Button for the following four operations
(8) Search the balance of an account holder by id and display balance by JOptionPane. Provide a method searchBalanceById(SavingAccount[] ….., int …..)
(9) Add an interest to the account holder by id. Provide method addInterestById(SavingAccount[] ….., int iID…., double rate)
method should call deposit(…). Note addInterestById(…..) returns amount to deposit.
(10) Display all information about account holders by accountType using JOptionPane.
Provide a method displayAllByAccountType (SavingAccount[ ], char  accountType)
(10b) Exit
(Note initially the “Text boxes” are disabled for all above cases. But if we select the radio button then the “TextBoxes” are enabled.)
*/
import javax.swing.*;
import java.util.*;


class BankAccount
{
    private String name;
    private int id;
    private char type;
    private double balance;

    BankAccount(String name, int id, char type, double balance)
    {
        this.name = name;
        this.id = id;
        this.type = type;
        this.balance = balance;
    }

    public String get_name()
    {
        return name;
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
        System.out.println(name);
        System.out.println(id);
        System.out.println(type);
        System.out.println(balance);
    }
}


class SavingAccount extends BankAccount
{
    private double rate;

    SavingAccount(String name, int id, char type, double balance,
                  double rate)
    {
        super(name, id, type, balance);
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

    public UseSavingBankAccount()
    {
        accounts = new SavingAccount[50];
        String name;
        char type;
        double balance = 2;
        double rate = 100;

        for (int i = 0; i < 50; i++) {
            name = "TTU";
            name += i;

            if (i % 2 == 0)
                type = 'c';
            else
                type = 's';

            balance += i;

            rate *= 0.5;

            accounts[i] = new SavingAccount(name, i, type, balance, rate);
        }
    }

    private SavingAccount find_acc(SavingAccount[] accs, int target)
    {
        SavingAccount account = null;
        for (SavingAccount acc : accs) {
            if (acc.get_id() == target) {
                account = acc;
            }
        }

        return account;
    }

    public double searchBalanceById(SavingAccount[] accs,
                                           int target)
    {
        double balance;

        SavingAccount account = find_acc(accs, target);
        if (account == null)
            balance = -1.0;
        else
            balance = account.get_balance();

        return balance;
    }

    public double addInterestById(SavingAccount[] accs, int target,
                                  double interest)
    {
        SavingAccount account = find_acc(accs, target);
        if (account != null)
            account.deposit(interest);

        double balance = account.get_balance();

        return balance;
    }

    public void displayAllByAccountType(SavingAccount[] accs,
                                               char type)
    {
        List<SavingAccount> filter = new ArrayList<SavingAccount>();
        // using a collection here, as the number of accounts of
        // a single type are theoretically unknown, can't use arr

        for (SavingAccount acc : accs) {
            if (acc.get_type() != type)
                continue;

            filter.add(acc);
        }

        SavingAccount[] filter_arr = new SavingAccount[filter.size()];
        filter.toArray(filter_arr);

        List<String> disp = new ArrayList<String>();
        for (SavingAccount acc : filter_arr) {
            String name = acc.get_name();
            int id = acc.get_id();
            double balance = acc.get_balance();
            char my_type = acc.get_type();

            String str = String.format("name: %s id: %d balance: %f " +
                                        "type: %c", name, id, balance,
                                        my_type);
            disp.add(str);
        }

        String[] disp_arr = new String[disp.size()];
        disp.toArray(disp_arr);

        JOptionPane.showMessageDialog(null, new JList<>(disp_arr));
    }
}


public class GrosHallHarper extends javax.swing.JFrame {

    /**
     * Creates new form Frame
     */

    private boolean r1_act = false;
    private boolean r2_act = false;
    private boolean r3_act = false;

    UseSavingBankAccount bank = new UseSavingBankAccount();

    public GrosHallHarper() {
        initComponents();

        ButtonGroup rg = new ButtonGroup();
        rg.add(r1);
        rg.add(r2);
        rg.add(r3);

        t1.setEnabled(false);
        t2.setEnabled(false);
        t3.setEnabled(false);
        t4.setEnabled(false);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        r1 = new javax.swing.JRadioButton();
        r2 = new javax.swing.JRadioButton();
        r3 = new javax.swing.JRadioButton();
        l1 = new javax.swing.JLabel();
        l2 = new javax.swing.JLabel();
        l3 = new javax.swing.JLabel();
        t1 = new javax.swing.JTextField();
        t2 = new javax.swing.JTextField();
        t3 = new javax.swing.JTextField();
        b1 = new javax.swing.JButton();
        b2 = new javax.swing.JButton();
        t4 = new javax.swing.JTextField();
        l4 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        r1.setText("Search Balance by ID");
        r1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                r1ActionPerformed(evt);
            }
        });

        r2.setText("Add Interest by ID");
        r2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                r2ActionPerformed(evt);
            }
        });

        r3.setText("Display All using AccountType");
        r3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                r3ActionPerformed(evt);
            }
        });

        l1.setText("ID");

        l2.setText("ID");

        l3.setText("AccountType");

        b1.setText("Submit");
        b1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                b1ActionPerformed(evt);
            }
        });

        b2.setText("Exit");
        b2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                b2ActionPerformed(evt);
            }
        });

        l4.setText("Interest");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(r3)
                        .addGap(18, 18, 18)
                        .addComponent(l3)
                        .addGap(123, 131, Short.MAX_VALUE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createSequentialGroup()
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addComponent(r1)
                                            .addComponent(r2))
                                        .addGap(0, 0, Short.MAX_VALUE))
                                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                        .addGap(0, 0, Short.MAX_VALUE)
                                        .addComponent(b1, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                    .addComponent(l2)
                                    .addComponent(l1)))
                            .addGroup(layout.createSequentialGroup()
                                .addGap(0, 0, Short.MAX_VALUE)
                                .addComponent(l4)))
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(t4)
                            .addComponent(b2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(t3)
                            .addComponent(t1, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                            .addComponent(t2))
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(r1)
                    .addComponent(t1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(l1))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(r2)
                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(t2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(l2)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(t4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(l4))
                .addGap(14, 14, 14)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(r3)
                    .addComponent(t3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(l3))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(b1)
                    .addComponent(b2))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void r1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_r1ActionPerformed
        r1_act = true;
        r2_act = false;
        r3_act = false;

        t1.setEnabled(true);
        t2.setEnabled(false);
        t3.setEnabled(false);
        t4.setEnabled(false);
    }//GEN-LAST:event_r1ActionPerformed

    private void r2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_r2ActionPerformed
        r1_act = false;
        r2_act = true;
        r3_act = false;

        t1.setEnabled(false);
        t2.setEnabled(true);
        t3.setEnabled(false);
        t4.setEnabled(true);
    }//GEN-LAST:event_r2ActionPerformed

    private void r3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_r3ActionPerformed
        r1_act = false;
        r2_act = false;
        r3_act = true;

        t1.setEnabled(false);
        t2.setEnabled(false);
        t3.setEnabled(true);
        t4.setEnabled(false);
    }//GEN-LAST:event_r3ActionPerformed

    private void b1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_b1ActionPerformed
        String str = "";
        if (r1_act) {
            int target = Integer.parseInt(t1.getText());
            double balance = bank.searchBalanceById(bank.accounts, target);

            if (balance < 0)
                str = "couldn't find a balance for that id!";
            else
                str = String.format("balance: %f%n", balance);
        }
        else if (r2_act) {
            int target = Integer.parseInt(t2.getText());
            double interest = Float.parseFloat(t4.getText());

            double balance = bank.addInterestById(bank.accounts, target, interest);

            str = String.format("new balance: (%f)%n", balance);
        }
        else if (r3_act) {
            char type = t3.getText().charAt(0);
            bank.displayAllByAccountType(bank.accounts, type);

            return;
        }

        JOptionPane.showMessageDialog(null, str);

    }//GEN-LAST:event_b1ActionPerformed

    private void b2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_b2ActionPerformed
        System.exit(0);
    }//GEN-LAST:event_b2ActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new GrosHallHarper().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton b1;
    private javax.swing.JButton b2;
    private javax.swing.JLabel l1;
    private javax.swing.JLabel l2;
    private javax.swing.JLabel l3;
    private javax.swing.JLabel l4;
    private javax.swing.JRadioButton r1;
    private javax.swing.JRadioButton r2;
    private javax.swing.JRadioButton r3;
    private javax.swing.JTextField t1;
    private javax.swing.JTextField t2;
    private javax.swing.JTextField t3;
    private javax.swing.JTextField t4;
    // End of variables declaration//GEN-END:variables
}
