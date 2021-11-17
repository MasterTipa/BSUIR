using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    private BoxCollider2D boxCollider;
    private Vector3 moveDelta;
    private RaycastHit2D hit;
    private Animator animator;
    // Start is called before the first frame update
    
    private void Start()
    {
        boxCollider = GetComponent<BoxCollider2D>();
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    private void FixedUpdate()
    {
        float x = Input.GetAxisRaw("Horizontal");
        float y = Input.GetAxisRaw("Vertical");

        moveDelta = new Vector3(x * 4, y * 4, 0);
        animator.SetFloat("speed", Mathf.Abs(moveDelta.magnitude));

        if (moveDelta.x > 0)
        {
            transform.localScale = Vector3.one;
        }
        else if (moveDelta.x < 0)
        {
            transform.localScale = new Vector3(-1, 1, 1);
        }

        hit = Physics2D.BoxCast(transform.position, 
                                boxCollider.size, 
                                0, 
                                new Vector2(0, moveDelta.y), 
                                Mathf.Abs(moveDelta.y * Time.deltaTime), 
                                LayerMask.GetMask("Humans", "Walls"));
        
        if (hit.collider == null)
        {
            transform.Translate(0, moveDelta.y * Time.deltaTime, 0);
        }
        
        hit = Physics2D.BoxCast(transform.position, 
                                boxCollider.size, 
                                0, 
                                new Vector2(moveDelta.x, 0), 
                                Mathf.Abs(moveDelta.x * Time.deltaTime), 
                                LayerMask.GetMask("Humans", "Walls"));
        
        if (hit.collider == null)
        {
            transform.Translate(moveDelta.x * Time.deltaTime, 0, 0);
        }
    }
}
