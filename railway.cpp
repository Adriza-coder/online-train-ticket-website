#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
using namespace std;

struct Train {
    int number;
    string name;
    string source;
    string destination;
    float fare;
};

int main() {
    cout << "Content-Type: text/html\n\n";

    Train trains[3] = {
        {101, "Rajdhani Express", "Delhi", "Mumbai", 1500},
        {102, "Shatabdi Express", "Delhi", "Kolkata", 2000},
        {103, "Duronto Express", "Delhi", "Chennai", 2500}
    };

    string query = getenv("QUERY_STRING") ? getenv("QUERY_STRING") : "";
    map<string, string> formData;

    size_t start = 0;
    while (start < query.length()) {
        size_t equalPos = query.find('=', start);
        size_t ampPos = query.find('&', start);

        if (equalPos == string::npos) break;

        string key = query.substr(start, equalPos - start);
        string value = (ampPos == string::npos) ?
                       query.substr(equalPos + 1) :
                       query.substr(equalPos + 1, ampPos - equalPos - 1);

        for (char &c : value) {
            if (c == '+') c = ' ';
        }

        formData[key] = value;
        if (ampPos == string::npos) break;
        start = ampPos + 1;
    }

    string name = formData["name"];
    int age = stoi(formData["age"]);
    string gender = formData["gender"];
    int trainNo = stoi(formData["train"]);
    int seats = stoi(formData["seats"]);

    Train selectedTrain;
    bool found = false;
    for (int i = 0; i < 3; i++) {
        if (trains[i].number == trainNo) {
            selectedTrain = trains[i];
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "<h1>Invalid Train Selection</h1>";
        return 0;
    }

    float totalFare = seats * selectedTrain.fare;

    cout << "<!DOCTYPE html><html><head><title>Booking Confirmation</title>";
    cout << "<style>"
         << "body { font-family: Arial; background-color: #f4f4f4; text-align:center; }"
         << ".ticket { background: white; padding: 20px; margin: auto; width: 50%; border-radius: 10px; box-shadow: 0px 0px 10px #ccc; }"
         << "h1 { color: green; }"
         << "table { width: 100%; border-collapse: collapse; margin-top: 20px; }"
         << "td, th { border: 1px solid #ddd; padding: 8px; }"
         << "th { background-color: #4CAF50; color: white; }"
         << ".back-btn { display: inline-block; margin-top: 20px; padding: 10px 20px; background: #4CAF50; color: white; text-decoration: none; border-radius: 5px; }"
         << "</style></head><body>";

    cout << "<div class='ticket'>";
    cout << "<h1>Booking Confirmed!</h1>";
    cout << "<table>";
    cout << "<tr><th>Passenger Name</th><td>" << name << "</td></tr>";
    cout << "<tr><th>Age</th><td>" << age << "</td></tr>";
    cout << "<tr><th>Gender</th><td>" << gender << "</td></tr>";
    cout << "<tr><th>Train</th><td>" << selectedTrain.name << " (" << selectedTrain.number << ")</td></tr>";
    cout << "<tr><th>Route</th><td>" << selectedTrain.source << " → " << selectedTrain.destination << "</td></tr>";
    cout << "<tr><th>Seats</th><td>" << seats << "</td></tr>";
    cout << "<tr><th>Total Fare</th><td>Rs. " << totalFare << "</td></tr>";
    cout << "</table>";
    cout << "<a href='/indianrailways/train_form.html' class='back-btn'>Book Another Ticket</a>";
    cout << "</div>";

    cout << "</body></html>";
    return 0;
}
