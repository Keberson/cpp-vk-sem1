## WEB development VK Park Semester №1
# Матрчиный калькулятор

*Задание выполнял Кузов Максим Юрьевич WEB-13*
Необходимо реализовать упрощённую версию упорядоченного множества из STL Set<T>. Асимптотики всех операций должны быть аналогичными std::set. Сравнение элементов типа T осуществлять только при помощи оператора <.
Необходимо поддержать следующие методы:
1) методы жизненного цикла - 4б
- конструктор по умолчанию;
- конструктор, принимающий пару итераторов элементов типа T, последовательно вставляемых в контейнер;
- конструктор, принимающий std::initializer_list элементов типа T;
- конструктор копирования ("глубокое копирование всех узлов контейнера");
- оператор присваивания;
- деструктор;

2) класс должен предоставлять const bidirectional-итератор для доступа к элементам, а также методы begin и end и позволять просматривать все элементы контейнера без возможности их изменения, перемещаясь от каждого к следующему/предыдущему за O(1). Так как контейнер упорядоченный, то подразумевается их перебор в порядке возрастания - 4б;

3) методы insert и erase вставки и удаления элементов из контейнера. Тип возвращаемого значения - void, При наличии/отсутствии элемента ничего делать не нужно. При модификации контейнера любой из этих операций итераторы могут инвалидироваться - 3б;

4) константные методы:
- size и empty, возвращающие количество элементов и true/false в зависимости от наличия элементов в контейнере - 1б;
- find и lower_bound, которые возвращают соответственно итератор на искомый элемент во множестве/первый элемент, который не меньше искомого (или end() при его отсутствии) - 3б.

Для базовой проверки корректности работоспособности контейнера можно использовать программу https://gist.github.com/leshiy1295/6667bfad5c4a3f05630c2b80e0be6f6c
При реализации собственных юнит-тестов рекомендуется в т.ч. сравнивать результаты и время работы собственной реализации Set с std::set на случайном наборе данных и разных операциях.