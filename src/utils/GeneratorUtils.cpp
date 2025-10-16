#include "GeneratorUtils.h"

void GeneratorUtils::initializeEntries(AdminService *service) {
    service->addDog("Max", "Bulldog", 2, "https://upload.wikimedia.org/wikipedia/commons/thumb/b/bf/Bulldog_inglese.jpg/1200px-Bulldog_inglese.jpg");
    service->addDog("Bella", "Poodle", 4, "https://www.dogster.com/wp-content/uploads/2023/08/red-toy-poodle-in-the-park_Mykhaylo_Kozelko_Shutterstock.jpg");
    service->addDog("Lucy", "Dachshund", 5, "https://upload.wikimedia.org/wikipedia/commons/b/be/%EB%8B%A5%EC%8A%A4%ED%9B%88%ED%8A%B8%28%EB%8B%A8%EB%AA%A8%EC%A2%85%29_%28Dachshund_%28Short%29%29.jpg");
    service->addDog("Molly", "Boxer", 3, "https://upload.wikimedia.org/wikipedia/commons/6/6f/Male_fawn_Boxer_undocked.jpg");
    service->addDog("Lola", "Pug", 1, "https://cdn.britannica.com/35/233235-050-8DED07E3/Pug-dog.jpg");
    service->addDog("Rocky", "Rottweiler", 5, "https://upload.wikimedia.org/wikipedia/commons/9/9b/Rocky_9_month.PNG");
    service->addDog("Ben", "Golden Retriever", 7, "https://pettownsendvet.com/wp-content/uploads/2023/01/iStock-1052880600-1024x683.jpg");
    service->addDog("Charlie", "Beagle", 1, "https://cdn.outsideonline.com/wp-content/uploads/2023/03/Funny_Dog_S.jpg");
    service->addDog("Daisy", "Labrador", 2, "https://upload.wikimedia.org/wikipedia/commons/thumb/3/34/Labrador_on_Quantock_%282175262184%29.jpg/1280px-Labrador_on_Quantock_%282175262184%29.jpg");
    service->addDog("Takamoto", "Shiba Inu", 1, "https://i.pinimg.com/236x/3d/97/f5/3d97f535ea5ee363d7ef69a5698b22ad.jpg");
}
