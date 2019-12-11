// collin gros
// 03/01/19

class Student
{
    private String name;
    private double marks;

    Student(String name, double marks)
    {
        this.name = name;
        this.marks = marks;
    }

    public static String generate_marks_report(Student[] students)
    {
        String last = "";

        for (int i = 0; i < students.length; i++) {
            Student student = students[i];
            String name = student.get_name();

            boolean found = false;
            for (int d = 0; d < name.length(); d++) {
                char c = name.charAt(d);

                if (found) {
                    last += Character.toString(c);
                }

                if (c == ' ') {
                    found = true;
                }
            }

            last += "\t";
            double marks = student.get_marks();
            last += Double.toString(marks);

            last += "\n";
        }

        return last;
    }

    public double get_marks()
    {
        return this.marks;
    }

    public String get_name()
    {
        return this.name;
    }

    public static void display(String str)
    {
        System.out.println(str);
    }
}
