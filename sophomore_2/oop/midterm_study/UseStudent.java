// collin gros
// 03/01/19

class UseStudent
{
    public static void main (String[] args)
    {
        Student[] students = new Student[3];
        students[0] = new Student("Collin Gros", 99.5);
        students[1] = new Student("Amanda Gros", 85.5);
        students[2] = new Student("Brooke Payton", 100.0);

        String report = Student.generate_marks_report(students);
        Student.display(report);

    }
}
