using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PipeSpawner : MonoBehaviour
{

    [SerializeField]
    private GameObject pipeHolder;

    // Use this for initialization
    void Start()
    {
        StartCoroutine(_Spawner());
    }

    IEnumerator _Spawner()
    {
        Vector3 tmp = pipeHolder.transform.position;
        yield return new WaitForSeconds(2);
        tmp.y = Random.Range(-2.5f, 2.5f);
        Instantiate(pipeHolder, tmp, Quaternion.identity);
        StartCoroutine(_Spawner());
    }
}
