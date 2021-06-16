using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

/*
 * 模拟物体的传输过程
 * 挂载在被传输物体上
 */
public class transmission : MonoBehaviour
{
    // Start is called before the first frame update
    private NavMeshAgent _navPlayer;
    private NavMeshPath _navPath;
    private static float tileSpacing = 0.4f;
    //path logo
    private GameObject directionPrefab;
    private List<GameObject> arrowList = new List<GameObject>();
    public Vector3 bg;
    public Vector3 ed;
    //begin flag
    public bool bf = false;
    public float time;
    public int index;
    //是否错误
    bool iswrong = false;
    void Start()
    {

    }
    bool movement(float time)
    {
        //gameObject.AddComponent<NavMeshAgent>();
        bg = gameObject.transform.position;
        Hashtable setting = new Hashtable(); setting.Add("position", ed); setting.Add("time", time);
        iTween.MoveTo(gameObject, setting);
        DrawPath(ed, bg);
        return true;
    }
    //设置路径
    public void setting(Vector3 end, float time, bool isw)
    {
        this.bf = true;
        this.ed = end;
        this.time = time;
        this.iswrong = isw;
    }
    public static List<GameObject> SDrawPath(Vector3 end, Vector3 begin)
    {
        //Debug.LogError(end.x - begin.x);
        /*if (!end.x.-begin.x)) Debug.LogError("aaaaaaaaaa");*/
        List<GameObject> arrows = new List<GameObject>();
        Quaternion planerot = Quaternion.identity;
        Vector3 offsetVector = end - begin;
        planerot = Quaternion.LookRotation(offsetVector);
        //Debug.Log(planerot.eulerAngles.x + " " + planerot.eulerAngles.y + " " + planerot.eulerAngles.z);
        float distance = Vector3.Distance(end, begin);
        float newSpacing = 0;
        //加载path预制体
        GameObject directionPrefab = Resources.Load("nav") as GameObject;
        for (int j = 0; j < distance / tileSpacing - 2; j += 2)

        {
            newSpacing += tileSpacing * 2;
            var normalizedVector = offsetVector.normalized;
            var position = begin + newSpacing * normalizedVector;
            GameObject go = Instantiate(directionPrefab, position, planerot);
            go.transform.Rotate(new Vector3(-90, 0, 0), Space.Self);
            if (!(Mathf.Abs(end.x - begin.x) < 0.01))
                go.transform.Rotate(new Vector3(0, 90, 0), Space.Self);
            arrows.Add(go);
        }
        return arrows;
    }
    //绘制路径--非静态
    void DrawPath(Vector3 end, Vector3 begin)
    {
        List<GameObject> arrows = arrowList;
        Quaternion planerot = Quaternion.identity;
        Vector3 offsetVector = end - begin;
        planerot = Quaternion.LookRotation(offsetVector);
        Debug.Log(planerot.eulerAngles.x + " " + planerot.eulerAngles.y + " " + planerot.eulerAngles.z);
        float distance = Vector3.Distance(end, begin);
        float newSpacing = 0;
        //加载path预制体
        if (iswrong) directionPrefab = Resources.Load("nav2") as GameObject;
        else directionPrefab = Resources.Load("nav") as GameObject;
        for (int j = 0; j < distance / tileSpacing - 2; j++)

        {
            newSpacing += tileSpacing;
            var normalizedVector = offsetVector.normalized;
            var position = begin + newSpacing * normalizedVector;
            GameObject go = Instantiate(directionPrefab, position, planerot);
            go.transform.Rotate(new Vector3(-90, 0, 0), Space.Self);
            go.transform.Rotate(new Vector3(0, 180, 0), Space.Self);
            arrowList.Add(go);
        }
    }
    // Update is called once per frame
    // 触发
    void Update()
    {
        if (bf)
        {
            movement(time);
            bf = false;
            //gameObject nxt=this.
            //WaitForSeconds;
        }
    }
}
