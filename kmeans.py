import numpy as np
import cv2
from matplotlib import pyplot as plt

def distancia_euclidiana(x1, x2):
    return np.sqrt(np.sum((x1 - x2) ** 2))

def set_cluster(arr, clusters):
    for i in range(arr.shape[0]):
        distancias = []
        for j in range(len(clusters)):
            dist = distancia_euclidiana(arr[i], clusters[j]["center"])
            distancias.append(dist)
        cluster_index = np.argmin(distancias)
        clusters[cluster_index]["points"].append(arr[i])
    return clusters
def update_cluster(arr, clusters):
    for i in range(len(clusters)):
        points = np.array(clusters[i]["points"])
        if len(points) > 0:
            new_center = np.mean(points, axis=0)
            clusters[i]["center"] = new_center
            clusters[i]["points"] = []
    return clusters

def pred_cluster(arr, clusters):
    pred = []
    for i in range(arr.shape[0]):
        distancias = []
        for j in range(len(clusters)):
            dist = distancia_euclidiana(arr[i], clusters[j]["center"])
            distancias.append(dist)
        cluster_index = np.argmin(distancias)
        pred.append(cluster_index)
    return pred

if __name__ == "__main__":
    img = cv2.imread("lena_color.tiff", cv2.IMREAD_COLOR)
    
    # transforma img em um arr de pixels
    arr = img.reshape((-1, 3))
    data = arr
    #print(arr)
    
    k = 3
    n = arr.shape[0] 
    clusters = {} 
    for i in range (k):
        points = []
        cluster = {
            "center": np.random.randint(0, 255, 3), # centro do cluster aleatorio,
            "points": []
        }
        clusters[i] = cluster
    # faz uma iteracao de treinamento apenas    
    altura, largura = img.shape[:2]
    clusters = set_cluster(arr, clusters)
    clusters = update_cluster(arr, clusters)
    pred = pred_cluster(arr,clusters)    
    
    # Reconstrucao da imagem
    clustered_image = np.zeros_like(arr)
    for i in range(len(pred)):
        clustered_image[i] = clusters[pred[i]]["center"]

    
    clustered_image = clustered_image.reshape((altura, largura, 3))
    cv2.imwrite("clustered_image.jpg", clustered_image)
    cv2.imshow("Imagem Original", img)
    cv2.imshow(f'Imagem Clusterizada (K={k})', clustered_image)

    while cv2.waitKey() != 27: # aperta esc
        pass

    cv2.destroyAllWindows()

    
