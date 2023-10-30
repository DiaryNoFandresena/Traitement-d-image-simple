#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// Prototypes des fonctions
void convertToGray(const Mat& inputImage, Mat& outputImage);
void resizeImage(const Mat& inputImage, Mat& outputImage, int width, int height);
void applyGaussianBlur(const Mat& inputImage, Mat& outputImage, int kernelSize);
void detectAndDrawContours(const Mat& inputImage, Mat& outputImage);
void NoirEtBlanc(const Mat& inputImage, Mat& outputImage);
void FloydSteinbergDithering(const Mat& inputImage, Mat& outputImage);
void Negatif(const Mat& inputImage, Mat& outputImage);
void applyCustomFilter(const Mat& inputImage, Mat& outputImage);
void applyMedianBlur(const Mat& inputImage, Mat& outputImage, int kernelSize);
void applySobel(const Mat& inputImage, Mat& outputImage);
void applyCanny(const Mat& inputImage, Mat& outputImage, double threshold1, double threshold2);
void rotateImage(const Mat& inputImage, Mat& outputImage, double angle);
void adjustBrightness(const Mat& inputImage, Mat& outputImage, int brightness);
void adjustContrast(const Mat& inputImage, Mat& outputImage, double contrast);
void addVignette(const Mat& inputImage, Mat& outputImage, double factor);
void cropToSquare(const Mat& inputImage, Mat& outputImage);
void compressImage(const Mat& inputImage, std::vector<uchar>& compressedImage, int quality);
void decompressImage(const std::vector<uchar>& compressedImage, Mat& outputImage);
void calculateHistogram(const Mat& inputImage, Mat& histogram);
void displayHistogram(const Mat& histogram);
void equalizeImageHistogram(const Mat& inputImage, Mat& outputImage); 

int main() {
    // ajoute l'image
    Mat inputImage = imread("image.jpg");
    
    //teste si l'image est fonctionnel
    if (inputImage.empty()) {
        cerr << "Erreur de chargement de l'image" << endl;
        return -1;
    }

    Mat outputImage;
    int choice = -1;
    int choices(0);

    vector<uchar> compressedImage;
    Mat decompressedImage;
    Mat histogram;

    cout << "Cette programme permet de traiter l'image " << endl;
    cout << "veuillez choisir le traitement que tu veux appliqué à ton image" <<endl;

    //menu du programme
    while (choice != 0) {
        cout << "Menu de traitement d'image" << endl;
        cout << "1 - Transformer votre image en niveaux de gris" << endl;
        cout << "2 - Redimensionner l'image" << endl;
        cout << "3 - Appliquer un filtre Gaussien" << endl;
        cout << "4 - Détecter et dessiner les contours" << endl;
        cout << "5 - Convertir en noir et blanc" << endl;
        cout << "6 - Dithering de Floyd-Steinberg" << endl;
        cout << "7 - Créer l'image négative" << endl;
        cout << "8 - Appliquer un filtre personnalisé" << endl;
        cout << "9 - Appliquer un filtre de médiane" << endl;
        cout << "10 - Appliquer un filtre de Sobel" << endl;
        cout << "11 - Appliquer l'algorithme de Canny" << endl;
        cout << "12 - Rotation de l'image" << endl;
        cout << "13 - Augmenter la luminosité" << endl;
        cout << "14 - Diminuer la luminosité" << endl;
        cout << "15 - Augmenter le contraste" << endl;
        cout << "16 - Diminuer le contraste" << endl;
        cout << "17 - Rogner l'image en carré" << endl;
        cout << "18 - Compresser l'image en JPEG" << endl;
        cout << "19 - Décompresser l'image" << endl;
        cout << "20 - calcule l'histogramme de l'image" << endl;
        cout << "21 - Égaliser l'histogramme" << endl;
        cout << "0 - Quitter" << endl;
        cout << "Choisissez une option : ";
        cin >> choice;
        
        //teste si l'imput saisie par l'utilisateur est correcte
        if (cin.fail() || choice < 0 || choice > 21) {
            cout << "Veuillez entrer un choix valide (un nombre entre 0 et 21)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice =-1;
        }
        else{
            switch (choice) {
                case 1:{
                    convertToGray(inputImage, outputImage);
                    imshow("Niveaux de gris", outputImage);
                    waitKey(0);
                    break;
                }
                case 2:{
                    int width(0), height(0);
                    bool case2status(true);
                    while (case2status) {
                        cout << "Entrez la largeur : ";
                        cin >> width;
                        if (cin.fail()) {
                            cout << "Veuillez entrer un nombre entier valide." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } 
                        else {
                            cout << "Entrez l'hauteur : ";
                            cin >> height;   
                            if(cin.fail()) {
                                cout << "Veuillez entrer un nombre entier valide." << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            else{
                                resizeImage(inputImage, outputImage, width, height);
                                imshow("Redimensionnement", outputImage);
                                waitKey(0);
                                case2status = false;
                            }
                        }
                    }
                    break;  // Sort de la boucle si l'entrée est valide
                }

                case 3:
                    int kernelSize;
                    cout << "Entrez la taille du noyau : ";
                    cin >> kernelSize;
                    if(cin.fail()) {
                                cout << "Veuillez entrer un nombre entier valide." << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else{
                        applyGaussianBlur(inputImage, outputImage, kernelSize);
                        imshow("Filtre Gaussien", outputImage);
                        waitKey(0);
                        break;
                    }
                    
                case 4:
                    detectAndDrawContours(inputImage, outputImage);
                    imshow("Contours", outputImage);
                    waitKey(0);
                    break;
                case 5:
                    NoirEtBlanc(inputImage, outputImage);
                    imshow("Noir et Blanc", outputImage);
                    waitKey(0);
                    break;
                case 6:
                    FloydSteinbergDithering(inputImage, outputImage);
                    imshow("Dithering de Floyd-Steinberg", outputImage);
                    waitKey(0);
                    break;
                case 7:
                    Negatif(inputImage, outputImage);
                    imshow("Image Négative", outputImage);
                    waitKey(0);
                    break;
                case 8:
                    applyCustomFilter(inputImage, outputImage);
                    imshow("Filtre personnalisé", outputImage);
                    waitKey(0);
                    break;
                case 9:
                    applyMedianBlur(inputImage, outputImage, 5);
                    imshow("Filtre de médiane", outputImage);
                    waitKey(0);
                    break;
                case 10:
                    applySobel(inputImage, outputImage);
                    imshow("Filtre de Sobel", outputImage);
                    waitKey(0);
                    break;
                case 11:
                    applyCanny(inputImage, outputImage, 50, 150);
                    imshow("Algorithme de Canny", outputImage);
                    waitKey(0);
                    break;
                case 12:
                    rotateImage(inputImage, outputImage, 45.0);
                    imshow("Image Rotée", outputImage);
                    waitKey(0);
                    break;
                case 13:
                    adjustBrightness(inputImage, outputImage, 50);
                    imshow("Luminosité Augmentée", outputImage);
                    waitKey(0);
                    break;
                case 14:
                    adjustBrightness(inputImage, outputImage, -50);
                    imshow("Luminosité Diminuée", outputImage);
                    waitKey(0);
                    break;
                case 15:
                    adjustContrast(inputImage, outputImage, 2.0);
                    imshow("Contraste Augmenté", outputImage);
                    waitKey(0);
                    break;
                case 16:
                    adjustContrast(inputImage, outputImage, 0.5);
                    imshow("Contraste Diminué", outputImage);
                    waitKey(0);
                    break;
                case 17:
                    cropToSquare(inputImage, outputImage);
                    imshow("Image Rognée en Carré", outputImage);
                    waitKey(0);
                    break;
                case 18:
                    compressImage(inputImage, compressedImage, 90);
                    imshow("Image compressée", compressedImage);
                    waitKey(0);
                    break;
                case 19:
                    decompressImage(compressedImage, decompressedImage);
                    imshow("Image Décompressée", decompressedImage);
                    waitKey(0);
                    break;
                case 20:
                    calculateHistogram(inputImage, histogram);
                    displayHistogram(histogram);
                    break;
                case 21:
                    equalizeImageHistogram(inputImage, outputImage);
                    displayHistogram(outputImage);
                    waitKey(0);
                    break;
                case 0:
                    break;  // Quitter
                default:
                    cout << "Option invalide. Veuillez réessayer." << endl;
            }
        }
    }

    return 0;
}

/* ====================================definition des fonctions================================ */
// Définition des fonctions


void convertToGray(const Mat& inputImage, Mat& outputImage) {
    cvtColor(inputImage, outputImage, COLOR_BGR2GRAY);
    cout <<("1")<<endl;
}

void resizeImage(const Mat& inputImage, Mat& outputImage, int width, int height) {
    resize(inputImage, outputImage, Size(width, height));
    cout <<("2")<<endl;
}

void applyGaussianBlur(const Mat& inputImage, Mat& outputImage, int kernelSize) {
    GaussianBlur(inputImage, outputImage, Size(kernelSize, kernelSize), 0);
    cout <<("3")<<endl;
}

void detectAndDrawContours(const Mat& inputImage, Mat& outputImage) {
    Mat gray;
    cvtColor(inputImage, gray, COLOR_BGR2GRAY);
    Mat edges;
    Canny(gray, edges, 50, 150);
    std::vector<std::vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(outputImage, contours, -1, Scalar(0, 0, 255), 2);
    cout <<("4")<<endl;
}

void NoirEtBlanc(const Mat& inputImage, Mat& outputImage) {
    cvtColor(inputImage, outputImage, COLOR_BGR2GRAY);
    threshold(outputImage, outputImage, 128, 255, THRESH_BINARY);
    cout <<("5")<<endl;
}

void FloydSteinbergDithering(const Mat& inputImage, Mat& outputImage) {
    cvtColor(inputImage, outputImage, COLOR_BGR2GRAY);
    for (int y = 0; y < outputImage.rows; y++) {
        for (int x = 0; x < outputImage.cols; x++) {
            int oldPixel = outputImage.at<uchar>(y, x);
            int newPixel = (oldPixel < 128) ? 0 : 255;
            outputImage.at<uchar>(y, x) = newPixel;
            int error = oldPixel - newPixel;
            if (x < outputImage.cols - 1) {
                outputImage.at<uchar>(y, x + 1) += (error * 7) / 16;
            }
            if (y < outputImage.rows - 1) {
                if (x > 0) {
                    outputImage.at<uchar>(y + 1, x - 1) += (error * 3) / 16;
                }
                outputImage.at<uchar>(y + 1, x) += (error * 5) / 16;
                if (x < outputImage.cols - 1) {
                    outputImage.at<uchar>(y + 1, x + 1) += (error * 1) / 16;
                }
            }
        }
    }
    cout <<("6")<<endl;
}

void Negatif(const Mat& inputImage, Mat& outputImage) {
    bitwise_not(inputImage, outputImage);
    cout <<("7")<<endl;
}

void applyCustomFilter(const Mat& inputImage, Mat& outputImage) {
    // Implémentez ici un filtre personnalisé selon vos besoins
    // Par exemple, un filtre de flou :
    GaussianBlur(inputImage, outputImage, Size(5, 5), 0);
    cout <<("8")<<endl;
}

void applyMedianBlur(const Mat& inputImage, Mat& outputImage, int kernelSize) {
    medianBlur(inputImage, outputImage, kernelSize);
    cout <<("9")<<endl;
}

void applySobel(const Mat& inputImage, Mat& outputImage) {
    Mat gray;
    cvtColor(inputImage, gray, COLOR_BGR2GRAY);
    Mat gradX, gradY;
    Sobel(gray, gradX, CV_16S, 1, 0);
    Sobel(gray, gradY, CV_16S, 0, 1);
    convertScaleAbs(gradX, gradX);
    convertScaleAbs(gradY, gradY);
    addWeighted(gradX, 0.5, gradY, 0.5, 0, outputImage);
    cout <<("10")<<endl;
}

void applyCanny(const Mat& inputImage, Mat& outputImage, double threshold1, double threshold2) {
    Mat gray;
    cvtColor(inputImage, gray, COLOR_BGR2GRAY);
    Canny(gray, outputImage, threshold1, threshold2);
    cout <<("11")<<endl;
}

void rotateImage(const Mat& inputImage, Mat& outputImage, double angle) {
    Point2f center(inputImage.cols / 2, inputImage.rows / 2);
    Mat rotationMatrix = getRotationMatrix2D(center, angle, 1.0);
    warpAffine(inputImage, outputImage, rotationMatrix, inputImage.size());
    cout <<("12")<<endl;
}

void adjustBrightness(const Mat& inputImage, Mat& outputImage, int brightness) {
    inputImage.convertTo(outputImage, -1, 1, brightness);
    cout <<("13")<<endl;
}

void adjustContrast(const Mat& inputImage, Mat& outputImage, double contrast) {
    inputImage.convertTo(outputImage, -1, contrast, 0);
    cout <<("14")<<endl;
}

void addVignette(const Mat& inputImage, Mat& outputImage, double factor) {
    Mat kernel = getGaussianKernel(inputImage.cols, -1, CV_32F);
    Mat vignette = kernel * kernel.t();
    outputImage = inputImage.mul(vignette);
    cout <<("15")<<endl;
}

void cropToSquare(const Mat& inputImage, Mat& outputImage) {
    int minSize = std::min(inputImage.cols, inputImage.rows);
    int x = (inputImage.cols - minSize) / 2;
    int y = (inputImage.rows - minSize) / 2;
    Rect roi(x, y, minSize, minSize);
    outputImage = inputImage(roi);
    cout <<("16")<<endl;
}

void compressImage(const Mat& inputImage, std::vector<uchar>& compressedImage, int quality) {
    std::vector<int> compression_params;
    compression_params.push_back(IMWRITE_JPEG_QUALITY);
    compression_params.push_back(quality);
    imencode(".jpg", inputImage, compressedImage, compression_params);
    cout <<("17")<<endl;
}

void decompressImage(const std::vector<uchar>& compressedImage, Mat& outputImage) {
    outputImage = imdecode(compressedImage, IMREAD_COLOR);
    cout <<("18")<<endl;
}


// Calcule l'histogramme d'une image
void calculateHistogram(const Mat& inputImage, Mat& histogram) {
    Mat outputImage;
    convertToGray(inputImage, outputImage);
    int histSize = 256; // Nombre de bins de l'histogramme
    float range[] = {0, 256}; // Plage de valeurs des pixels (de 0 à 255)
    const float* histRange = {range};

    // Calcul de l'histogramme
    calcHist(&outputImage, 1, 0, Mat(), histogram, 1, &histSize, &histRange, true, false);
    cout <<("19")<<endl;
}

// Égalise l'histogramme d'une image
void equalizeImageHistogram(const Mat& inputImage, Mat& outputImage) {
    Mat inputImageGray;
    cvtColor(inputImage, inputImageGray, COLOR_BGR2GRAY);

    Mat equalizedImage;
    equalizeHist(inputImageGray, equalizedImage);

    cvtColor(equalizedImage, outputImage, COLOR_GRAY2BGR);
    cout <<("20")<<endl;
}

// Affiche l'histogramme 
void displayHistogram(const Mat& histogram) {
    int histSize = histogram.rows;
    double maxVal;
    minMaxLoc(histogram, 0, &maxVal, 0, 0);

    int scale = 2;
    Mat histImage = Mat::zeros(histSize * scale, 256 * scale, CV_8UC3);

    for (int i = 0; i < histSize; i++) {
        float value = histogram.at<float>(i);
        line(histImage, Point(i * scale, histSize * scale), Point(i * scale, (histSize - value) * scale), Scalar(0, 0, 255), scale);
    }

    imshow("Histogram", histImage);
    cout <<("21")<<endl;
}