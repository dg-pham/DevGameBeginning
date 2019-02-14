using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PipeHolder : MonoBehaviour
{

    public float speed;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (BirdController.instance != null)
        {
            if (BirdController.instance.flag == 1)
            {
                Destroy(GetComponent<PipeHolder>());

            }
        }
        _pipeMovement();
    }

    void _pipeMovement()
    {
        Vector3 tmp = transform.position;
        tmp.x -= speed * Time.deltaTime;
        transform.position = tmp;
    }

    //void OnCollisionEnter2D(Collision2D collision)
    //{

    //}

    void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Destroy")
        {
            Destroy(gameObject);
        }
    }
}
