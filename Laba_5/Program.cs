using System.Diagnostics;
using System.Xml.Linq;
using static System.Net.Mime.MediaTypeNames;

namespace CinemaCsh {
    // Класс Cinema, представляющий информацию о фильмах в кинотеатре
    class Cinema
    { //Свойства
        public string movie_name { private set; get; } // Название фильма
        public int total_seats { private set; get; } // Общее количество мест
        public int viewers { private set; get; } // Количество зрителей
        public int ticket_price { private set; get; } // Стоимость билета
        public string session_time { private set; get; } // Время начала сеанса
        //Конструкторы
        public Cinema() { }
        public Cinema(string name, int seats, int view, int price, string time) {
            movie_name = name; 
            total_seats = seats; 
            viewers = view; 
            ticket_price = price; 
            session_time = time;
        }
        // Метод для вычисления процента заполнения зала
        public double getOccupancy() {
		return ((double)viewers / total_seats) * 100;
        }   
    }
    internal class Program {
        // Метод для вывода уникальных названий фильмов (пункт a)
        public static void DisplayUniqueMovieTitles(string filename) {
            try {
                var movieTitles = new HashSet<string>(); // Хэш-сет для уникальных названий

                // Чтение файла построчно
                foreach (var line in File.ReadLines(filename)) {
                    var movieName = line.Split(' ')[0]; // Первое слово - это название фильма
                    movieTitles.Add(movieName);         // Добавляем название в хэш-сет
                }

                Console.WriteLine("Перечень названий фильмов без повторов:");
                foreach (var title in movieTitles) {
                    Console.WriteLine(title);
                }
            }
            catch (Exception) {
                throw new Exception("Ошибка: Не удалось выполнить пункт а!");
            }
        }
    }
}
