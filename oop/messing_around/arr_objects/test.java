class Main
{
    public static void main(String[] args)
    {
        MyClass[] arr = new MyClass[5];

        for (int i = 0; i < arr.length; i++) {
            arr[i] = new MyClass(i);
        }

        for (int i = 0; i < arr.length; i++) {
            arr[i].print_num();
        }
    }
}
