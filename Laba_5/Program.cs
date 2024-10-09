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

        // Метод для вывода среднего процента заполнения зала для указанного фильма (пункт b)
        public static void DisplayMovieOccupancy(List<Cinema> cinemas, string movieName) {
            var selectedMovies = cinemas.Where(c => c.movie_name.Equals(movieName, StringComparison.OrdinalIgnoreCase)).ToList();

            if (selectedMovies.Count > 0) {
                double averageOccupancy = selectedMovies.Average(c => c.getOccupancy());
                Console.WriteLine($"Средний процент заполнения зала для фильма \"{movieName}\": {averageOccupancy:F2}%");
            }
            else {
                Console.WriteLine($"Фильм \"{movieName}\" не найден.");
            }
        }

        // Метод для чтения данных из файла и создания объектов Cinema
        public static List<Cinema> ReadCinemaData(string filename) {
            var cinemas = new List<Cinema>();

            try {
                // Чтение данных из файла и создание объектов Cinema
                foreach (var line in File.ReadLines(filename)) {
                    var parts = line.Split(' '); // Разделяем данные по пробелами

                    string name = parts[0];
                    int seats = int.Parse(parts[1]);
                    int view = int.Parse(parts[2]);
                    int price = int.Parse(parts[3]);
                    string time = parts[4];

                    cinemas.Add(new Cinema(name, seats, view, price, time));
                }
            }
            catch (Exception) {
                throw new Exception("Ошибка: Не удалось открыть файл!");
            }

            return cinemas;
        }
    }
}
