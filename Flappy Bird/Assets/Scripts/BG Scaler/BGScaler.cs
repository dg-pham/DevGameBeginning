using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BGScaler : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        SpriteRenderer sr = GetComponent<SpriteRenderer>();         //GetComponent: get from inspector
        Vector3 tmpScale = transform.localScale;                    //create a temp Scaler

        float width = sr.bounds.size.x;
        float height = sr.bounds.size.y;

        float bgHeight = Camera.main.orthographicSize * 2f;         //10  (camera main = 5)
        float bgWidth = bgHeight * Screen.width / Screen.height;    //10 * .. / ..

        tmpScale.x = bgWidth / width;
        tmpScale.y = bgHeight / height;

        transform.localScale = tmpScale;
    }

}
